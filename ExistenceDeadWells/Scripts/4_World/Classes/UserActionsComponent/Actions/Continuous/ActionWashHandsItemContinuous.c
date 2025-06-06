modded class ActionWashHandsWell
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

		if (!well) // If this is not a vanilla well, stop here. Some mods have their own "wells" that aren't Well types.
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
};