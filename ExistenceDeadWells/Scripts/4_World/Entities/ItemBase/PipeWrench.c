modded class PipeWrench extends Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionRepairWell);
	}
}