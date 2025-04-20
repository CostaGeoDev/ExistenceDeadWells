modded class ActionDrinkWellContinuous : ActionContinuousBase
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

    // When the player stops drinking add the cholera chance to the player
    override void OnEndServer(ActionData action_data)
    {
        super.OnEndServer(action_data);

        if (!action_data || !action_data.m_Player)
            return;

        int choleraChance;
        Well well = Well.Cast(action_data.m_Target.GetObject());

        if (well)
        {
            well.TransmitCholeraChance(action_data.m_Player, choleraChance);

            if (Math.RandomInt(0, 100) < choleraChance)
            {
                action_data.m_Player.InsertAgent(eAgents.CHOLERA, 1); // Assuming 'eAgents.CHOLERA' is the correct enum
            }
        }
    }
}