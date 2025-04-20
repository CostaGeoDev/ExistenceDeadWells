modded class Pliers extends ToolBase
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionRepairWell);
	}
}