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

function initialize()
{
	IrisBuild.initialize(fl.configDirectory);
}

function loadProject()
{
	var result = IrisBuild.loadProject(flash.getDocumentDOM().path);
	fl.trace("\"" + flash.getDocumentDOM().path + "\" is " + (result == "true" ? "up-to-date" : "out-of-date") + ".");
}

function openSolution()
{
	return fl.browseForFileURL("open", "Select a solution file.", "IrisBuild Solution (*.xml)", "xml");
}

function createSolution()
{
	path = fl.browseForFileURL("save", "Specify a filename for the solution file.", "IrisBuild Solution (*.xml)", "xml");
	return IrisBuild.createSolution(path) == "true" ? path : null;
}

function loadSolution(path)
{
	return IrisBuild.loadSolution(path) == "true";
}

function verifySolution()
{
	return IrisBuild.verifySolution() == "true";
}

function addProject()
{
	var path = fl.browseForFileURL("select", "Select a project file.", "Flash Uncompressed Document (*.xfl)", "xfl");
	if (!path)
	{
		return false;
	}
	
	return IrisBuild.addProject(path) == "true";
}

function removeProject(path)
{
	return IrisBuild.removeProject(path) == "true";
}

function getSolutionTreeDataProvider()
{
	return IrisBuild.getSolutionTreeDataProvider();
}

function buildProjects()
{
	return IrisBuild.buildProjects();
}

function getSettingInt(setting)
{
	return IrisBuild.getSettingInt(setting);
}

function getSettingString(setting)
{
	return IrisBuild.getSettingString(setting);
}

function setSettingInt(setting, value)
{
	IrisBuild.setSettingInt(setting, value);
}

function setSettingString(setting, value)
{
	IrisBuild.setSettingString(setting, value);
}