import flash.events.Event;
import mx.controls.Alert;
import mx.events.CloseEvent;
import mx.managers.PopUpManager;

public function onClose(e:CloseEvent):void
{
	PopUpManager.removePopUp(this);
}

public function onBtnSaveClicked(e:Event):void
{
	PopUpManager.removePopUp(this);
}

public function onBtnCancelClicked(e:Event):void
{
	PopUpManager.removePopUp(this);
}