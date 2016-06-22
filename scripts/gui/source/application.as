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
	execute("loadSolution", path);
	
	_solutionTreeData = XML(execute("getSolutionTreeDataProvider"));
	treSolution.expandItem(_solutionTreeData.root.getItemAt(0), true);
	
	var persistentData:SharedObject = SharedObject.getLocal("persistentData");
	persistentData.data.IrisBuild_CurrentSolution = path;
	
	_targetSolutionURI = path;
}