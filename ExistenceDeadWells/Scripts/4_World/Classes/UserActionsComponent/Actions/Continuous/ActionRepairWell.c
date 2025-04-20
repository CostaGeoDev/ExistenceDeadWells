class ActionRepairWellCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        float time_taken_pipe_wrench = 15;
        float time_taken_wrench = 30;
        float time_taken_pliers = 60;

        if (m_ActionData.m_MainItem.GetType() == "Wrench")
        {
            m_ActionData.m_ActionComponent = new CAContinuousTime(time_taken_wrench);
        }
        else if (m_ActionData.m_MainItem.GetType() == "PipeWrench")
        {
            m_ActionData.m_ActionComponent = new CAContinuousTime(time_taken_pipe_wrench);
        }
        else if (m_ActionData.m_MainItem.GetType() == "Pliers")
        {
            m_ActionData.m_ActionComponent = new CAContinuousTime(time_taken_pliers);
        }
        else
        {
            m_ActionData.m_ActionComponent = new CAContinuousTime(time_taken_wrench); // Default case
        }
    }
};

class ActionRepairWell : ActionContinuousBase
{
    void ActionRepairWell()
    {
        m_CallbackClass = ActionRepairWellCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTCursor(UAMaxDistances.SMALL);
    }

    override string GetText()
    {
        return "#Repair this well";
    }

    override bool IsLockTargetOnUse()
	{
		return false;
	}

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Well well = Well.Cast(target.GetObject());

        if (!well)
			return false;

        if (GetGame().IsDedicatedServer() && well.IsRepaired())
        {
            player.DeadWell_Message(GetDeadWellConfig().messageFixed);
            return false;
        }

        return !well.IsRepaired();
    }

    override void OnFinishProgressServer(ActionData action_data)
	{
		PlayerBase player = action_data.m_Player;

		Well well = Well.Cast(action_data.m_Target.GetObject());

		if (!well)
			return;

		well.SetRepaired(true);

        int wellIndex = GetDeadWellConfig().GetRepairableWellIndex(well.GetPosition());
        GetDeadWellConfig().SetWellRepaired(wellIndex, well.GetPosition(), true, true);
        action_data.m_MainItem.DecreaseHealth("", "", GetDeadWellConfig().toolDamage);
    }

    override void OnStartAnimationLoop( ActionData action_data )
    {
        super.OnStartAnimationLoop( action_data );

        if ( !GetGame().IsMultiplayer() || GetGame().IsServer() )
		{
			Param2<bool, string> play = new Param2<bool, string>( true, "wrench_loop_SoundSet" );
			GetGame().RPCSingleParam( action_data.m_MainItem, ERPCs.RPC_SOUND_LOCK_ATTACH, play, true );
		}
    }

    override void OnEnd( ActionData action_data )
    {
        if ( !GetGame().IsMultiplayer() || GetGame().IsServer() )
        {
			Param2<bool, string> play = new Param2<bool, string>( false, "wrench_loop_SoundSet" );
			GetGame().RPCSingleParam( action_data.m_MainItem, ERPCs.RPC_SOUND_LOCK_ATTACH, play, true );
		}
    }

    override void OnEndAnimationLoop( ActionData action_data )
	{
		super.OnEndAnimationLoop( action_data );

		if ( !GetGame().IsMultiplayer() || GetGame().IsServer() )
		{
			Param2<bool, string> play = new Param2<bool, string>( false, "wrench_loop_SoundSet" );
			GetGame().RPCSingleParam( action_data.m_MainItem, ERPCs.RPC_SOUND_LOCK_ATTACH, play, true );
		}
	}
};