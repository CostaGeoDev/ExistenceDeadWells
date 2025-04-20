class CfgPatches
{
	class DeadWells
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Scripts",
			"DZ_Data"
		};
	};
};
class CfgMods
{
	class DeadWells
	{
		dir="ExistenceDeadWells";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="ExistenceDeadWells";
		credits="CostaGeo";
		author="";
		authorID="0";
		version="1.0";
		extra=0;
		type="mod";
		inputs="";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"ExistenceDeadWells/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"ExistenceDeadWells/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"ExistenceDeadWells/Scripts/5_Mission"
				};
			};
		};
	};
};
