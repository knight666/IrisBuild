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