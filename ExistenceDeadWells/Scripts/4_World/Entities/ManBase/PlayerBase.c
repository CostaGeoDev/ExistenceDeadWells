modded class PlayerBase
{
    protected bool m_PreventUseWell = false;

    override void Init()
    {
        super.Init();
        RegisterNetSyncVariableBool("m_PreventUseWell");
    }

    void SetPreventUseWell(bool prevent)
    {
        m_PreventUseWell = prevent;
        SetSynchDirty();
    }

    bool IsPreventUseWell()
    {
        return m_PreventUseWell;
    }

    void DeadWell_Message(string message)
    {
        if (!IsAlive() || IsPlayerDisconnected() || !GetIdentity())
			return;

        Param1<string> msgParam;
        msgParam = new Param1<string>(message);
        GetGame().RPCSingleParam(this, ERPCs.RPC_USER_ACTION_MESSAGE, msgParam, true, GetIdentity());
    }

    void DeadWell_MessageDelayed(string message, float timeDelay)
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeadWell_Message, timeDelay * 1000, false, message);
    }
}