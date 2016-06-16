import adobe.utils.MMExecute;
import mx.collections.XMLListCollection;
import flash.events.Event;
import flash.net.SharedObject;

private var _targetSolutionURI:String = "";

[Bindable]
private var _solutionTreeData:XML = <root />;

[Bindable]
[Embed(source="assets/Checked.png")] 
public var iconClean:Class; 

[Bindable]
[Embed(source="assets/Attention.png")] 
public var iconDirty:Class; 

private function execute(... parameters):String
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
	
	return MMExecute(scriptPath);
}

private function onCreationComplete(e:Event):void
{
	execute("initialize");
	
	var persistentData:SharedObject = SharedObject.getLocal("persistentData");
	if (persistentData && persistentData.data.hasOwnProperty("IrisBuild_CurrentSolution"))
	{
		loadSolution(persistentData.data.IrisBuild_CurrentSolution);
	}
}

private function onBtnNewClicked(e:Event):void
{
	var path:String = execute("createSolution");
	if (path != "null")
	{
		loadSolution(path);
	}
}

private function onBtnLoadClicked(e:Event):void
{
	var path:String = execute("openSolution");
	if (path != "null")
	{
		loadSolution(path);
	}
}

private function onBtnCheckClicked(e:Event):void
{
	execute("verifySolution");
	
	_solutionTreeData = XML(execute("getSolutionTreeDataProvider"));
	treSolution.expandItem(_solutionTreeData.root.getItemAt(0), true);
}

private function onBtnBuildClicked(e:Event):void
{

}

private function onBtnAddProjectClicked(e:Event):void
{
	
}

private function onBtnRemoveProjectClicked(e:Event):void
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