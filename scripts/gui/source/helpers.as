import adobe.utils.MMExecute;

public var IRIS_SETTING_LOGGER_LEVEL:Number = 1;

public function flashTrace(message:String):void
{
	MMExecute('fl.trace("' + message + '");');
}

public function execute(... parameters):String
{
	var scriptPath:String = "fl.runScript(fl.configURI + 'IrisBuild/jsfl/interface.jsfl', '" + parameters.shift().toString() + "'";
	
	var args:Array = [];
	for (var i:int = 0; i < parameters.length; i++)
	{
		if (parameters[i] is Number)
		{
			args.push(String(parameters[i]));
		}
		else
		{
			args.push("'" + (parameters[i] || "").split("'").join("\'") + "'");
		}
	}
	
	if (args.length > 0)
	{
		scriptPath += ", " + args.join(", ");
	}
	
	scriptPath += ");";
	
	flashTrace(scriptPath);
	
	return MMExecute(scriptPath);
}

private function loadSettings():void
{
	var persistentData:SharedObject = SharedObject.getLocal("persistentData");
	if (!persistentData)
	{
		return;
	}
	
	persistentData.data.IrisBuild_LoggerMaximumLevel = execute("getSettingInt", IRIS_SETTING_LOGGER_LEVEL) as Number;
}

private function saveSettings():void
{
	var persistentData:SharedObject = SharedObject.getLocal("persistentData");
	if (!persistentData)
	{
		return;
	}
	
	execute("setSettingInt", IRIS_SETTING_LOGGER_LEVEL, persistentData.data.IrisBuild_LoggerMaximumLevel);
}