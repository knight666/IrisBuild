import flash.events.Event;
import mx.controls.Alert;
import mx.events.CloseEvent;
import spark.events.IndexChangeEvent;
import mx.managers.PopUpManager;

public function onCreationComplete(e:Event):void
{
	var persistentData:SharedObject = SharedObject.getLocal("persistentData");
	if (persistentData)
	{
		drpLogging.selectedIndex = persistentData.data.IrisBuild_LoggerMaximumLevel;
	}
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