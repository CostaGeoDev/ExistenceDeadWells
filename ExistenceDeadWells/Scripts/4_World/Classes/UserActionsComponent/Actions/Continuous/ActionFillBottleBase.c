modded class ActionFillBottleBase : ActionContinuousBase
{
    override bool CanContinue(ActionData action_data)
    {
        if (!action_data || !action_data.m_Player)
			return false;

        if (action_data.m_Player.IsPreventUseWell())
        {
            return false;
        }

        return super.CanContinue(action_data);
    }

    override void OnStartServer(ActionData action_data)
	{
		if (!action_data || !action_data.m_Player)
			return;

		Well well = Well.Cast(action_data.m_Target.GetObject());

		if (!well)
        {
            action_data.m_Player.SetPreventUseWell(false);
            return;
        }

        if (!well.IsRepaired())
        {
            action_data.m_Player.SetPreventUseWell(true);
            action_data.m_Player.MessageImportant(GetDeadWellConfig().messageCantDrink);
        }
        else
        {
            action_data.m_Player.SetPreventUseWell(false);
        }
    }

    // If enableWellTransferCholera is true, then the player has a chance to get cholera when drinking from the well.
    override void OnEndServer(ActionData action_data)
    {
        Well well = Well.Cast(action_data.m_Target.GetObject());

        if (well)
        {            
            if (well.GetDeadWellConfig().enableWellTransferCholera && well.GetDeadWellConfig().choleraChance > 0)
            {
                if (Math.RandomIntInclusive(0, 100) <= well.GetDeadWellConfig().choleraChance)
                {
                    action_data.m_MainItem.InsertAgent(eAgents.CHOLERA, 1);
                }
            }
        }
    }
}
