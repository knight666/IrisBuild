import flash.events.Event;
import mx.controls.Alert;
import mx.events.CloseEvent;
import spark.events.IndexChangeEvent;
import mx.managers.PopUpManager;

public function onCreationComplete(e:Event):void
{
	loadSettings();
}

public function onClose(e:CloseEvent):void
{
	PopUpManager.removePopUp(this);
}

public function onBtnSaveClicked(e:Event):void
{
	saveSettings();
	
	PopUpManager.removePopUp(this);
}

public function onBtnCancelClicked(e:Event):void
{
	PopUpManager.removePopUp(this);
}

public function onDrpLoggingChange(e:IndexChangeEvent):void
{
	var persistentData:SharedObject = SharedObject.getLocal("persistentData");
	if (!persistentData)
	{
		return;
	}
	
	persistentData.data.IrisBuild_LoggerMaximumLevel = e.currentTarget.selectedIndex;
}

private function loadSettings():void
{
	var persistentData:SharedObject = SharedObject.getLocal("persistentData");
	if (!persistentData)
	{
		return;
	}
	
	persistentData.data.IrisBuild_LoggerMaximumLevel = execute("getSettingInt", IRIS_SETTING_LOGGER_LEVEL);
	drpLogging.selectedIndex = persistentData.data.IrisBuild_LoggerMaximumLevel;
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