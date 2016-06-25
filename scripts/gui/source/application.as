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
import mx.collections.XMLListCollection;
import flash.events.Event;
import flash.net.SharedObject;
import mx.containers.TitleWindow;
import mx.managers.PopUpManager;

private var _targetSolutionURI:String = "";
private var _titleWindow:TitleWindow;

[Bindable]
private var _solutionTreeData:XML = <root />;

[Bindable]
[Embed(source="assets/Checked.png")] 
public var iconClean:Class; 

[Bindable]
[Embed(source="assets/Attention.png")] 
public var iconDirty:Class;

public function onCreationComplete(e:Event):void
{
	execute("initialize");
	
	loadSettings();
	
	var persistentData:SharedObject = SharedObject.getLocal("persistentData");
	if (persistentData && persistentData.data.hasOwnProperty("IrisBuild_CurrentSolution"))
	{
		loadSolution(persistentData.data.IrisBuild_CurrentSolution);
	}
}

public function onBtnNewClicked(e:Event):void
{
	var path:String = execute("createSolution");
	if (path != "null")
	{
		loadSolution(path);
	}
}

public function onBtnLoadClicked(e:Event):void
{
	var path:String = execute("openSolution");
	if (path != "null")
	{
		loadSolution(path);
	}
}

public function onBtnCheckClicked(e:Event):void
{
	execute("verifySolution");
	
	_solutionTreeData = XML(execute("getSolutionTreeDataProvider"));
	treSolution.expandItem(_solutionTreeData.root.getItemAt(0), true);
}

public function onBtnBuildClicked(e:Event):void
{
	execute("buildProjects");
}

public function onBtnSettingsClicked(e:Event):void
{
	_titleWindow = PopUpManager.createPopUp(this, Settings, true) as TitleWindow;
	PopUpManager.centerPopUp(_titleWindow);
}

public function onBtnAddProjectClicked(e:Event):void
{
	if (execute("addProject"))
	{
		var persistentData:SharedObject = SharedObject.getLocal("persistentData");
		loadSolution(persistentData.data.IrisBuild_CurrentSolution);
	}
}

public function onBtnRemoveProjectClicked(e:Event):void
{

}

private function loadSolution(path:String):void
{
	if (!execute("loadSolution", path))
	{
		flashTrace("Failed to load solution at \"" + path + "\".");
		
		return;
	}
	
	_solutionTreeData = XML(execute("getSolutionTreeDataProvider"));
	treSolution.expandItem(_solutionTreeData.root.getItemAt(0), true);
	
	var persistentData:SharedObject = SharedObject.getLocal("persistentData");
	persistentData.data.IrisBuild_CurrentSolution = path;
	
	_targetSolutionURI = path;
	
	return;
}