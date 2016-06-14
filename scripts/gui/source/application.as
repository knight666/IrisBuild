import adobe.utils.MMExecute;
import mx.collections.XMLListCollection;
import flash.events.Event;
import flash.net.SharedObject;

private var _targetSolutionURI:String = "";

[Bindable]
private var _solutionTreeData:XML =
	<root label="Solution">
		<node label= "Solution">
			<node label="Project1" />
			<node label="Project2" />
			<node label="Project3" />
			<node label="Project4" />
		</node>
	</root>;

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
		_targetSolutionURI = persistentData.data.IrisBuild_CurrentSolution;
		execute("loadSolution", _targetSolutionURI);
	}
}

private function onBtnLoadClicked(e:Event):void
{
	var path:String = execute("openSolution");
	if (path != "null")
	{
		execute("loadSolution", path);
		
		_targetSolutionURI = path;
	}
}