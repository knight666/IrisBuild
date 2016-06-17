import adobe.utils.MMExecute;

public var IRIS_SETTING_LOGGER_LEVEL:String = "1";

public function execute(... parameters):String
{
	var scriptPath:String = "fl.runScript(fl.configURI + 'IrisBuild/jsfl/interface.jsfl', '" + parameters.shift().toString() + "'";
	
	var args:Array = [];
	for (var i:int = 0; i < parameters.length; i++)
	{
		args.push("'" + (parameters[i] || "").split("'").join("\'") + "'");
	}
	
	if (args.length > 0)
	{
		scriptPath += ", " + args.join(",");
	}
	
	scriptPath += ");";
	
	// MMExecute('fl.trace("' + scriptPath + '");');
	
	return MMExecute(scriptPath);
}