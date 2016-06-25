/*
	Copyright (c) 2016 Bigpoint GmbH
	
	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.
*/

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
	
	// flashTrace(scriptPath);
	
	return MMExecute(scriptPath);
}

private function loadSettings():void
{
	var persistentData:SharedObject = SharedObject.getLocal("persistentData");
	if (!persistentData)
	{
		return;
	}
	
	if (persistentData.data.hasOwnProperty("IrisBuild_LoggerMaximumLevel"))
	{
		execute("setSettingInt", IRIS_SETTING_LOGGER_LEVEL, persistentData.data.IrisBuild_LoggerMaximumLevel);
	}
	else
	{
		persistentData.data.IrisBuild_LoggerMaximumLevel = Number(execute("getSettingInt", IRIS_SETTING_LOGGER_LEVEL));
	}
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