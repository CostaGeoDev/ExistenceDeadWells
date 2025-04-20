modded class MissionServer
{
    override void OnInit()
    {
        GetDeadWellConfig();
        super.OnInit();

        Print("[DeadWellConfig] OnInit - Loaded config successfully.");
    }

    void ~MissionServer()
    {
        GetDeadWellConfig().Save();
    }
}