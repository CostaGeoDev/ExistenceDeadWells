modded class Well extends BuildingSuper
{
    protected bool m_IsRepaired = false;

    // Returns this well's repaired state
    bool IsRepaired()
    {
        return m_IsRepaired;
    }

    // Sets this well's repaired state
    void SetRepaired(bool repaired)
    {
        m_IsRepaired = repaired;
    }

    // This is called whenever a new well is created (ie. loaded in on server startup)
    void Well()
    {
        #ifdef SERVER
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(SetupRepairableWell, 2500, false);
        #endif
    }

    // Sets this well's repaired state.
    void SetupRepairableWell()
    {
        int ts = JMDate.Now(false).GetTimestamp();
        int idx = GetDeadWellConfig().GetRepairableWellIndex(GetPosition());
        RepairableWell well = NULL;

        if (idx >= 0)
        {
            well = GetDeadWellConfig().RepairableWells.Get(idx);

            if (!well.Indestructible)
            {
                // If time stamp > well's repaired timestamp, set it back to broken
                if (ts > well.BrokenTime)
                {
                    GetDeadWellConfig().SetWellRepaired(idx, GetPosition(), false, false);
                }
            }
            else
            {
                GetDeadWellConfig().SetWellRepaired(idx, GetPosition(), true, false);
            }
        }

        if (well)
        {
            m_IsRepaired = well.Repaired;
        }
        else
        {
            m_IsRepaired = !GetDeadWellConfig().wellsDisabledDefault;
        }
    }

    // Returns the well's cholera chance (0-100), if enableWellTransferCholera is true, choleraChance sets the chance of cholera
    void TransmitCholeraChance(PlayerBase player, out int choleraChance)
    {
        choleraChance = 0;

        if (GetDeadWellConfig().enableWellTransferCholera && !IsRepaired())
        {
            choleraChance = GetDeadWellConfig().choleraChance;
        }
    }
}