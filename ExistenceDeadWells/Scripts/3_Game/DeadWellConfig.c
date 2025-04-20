class DeadWellConfig
{
    // Config file location in the server profile directory
    private const static string deadWellModFolder = "$profile:\\DeadWell\\";
    private const static string deadWellConfigName = "DeadWellConfig.json";

    // Static constant config version (used for versioning, not saved to JSON)
    static const string CONFIG_VERSION = "0.0.2";

    // Data fields stored in the configuration
	string ConfigVersion = ""; // Stores the current config version
    string CONFIG_DATA = "-----------------------------------------------------------------------------------------------------------------------"; // Divider for organization

    bool wellsDisabledDefault = true; // If true then all wells will be disabled by default
    int toolDamage = 100; // The amount of damage a tool will take when trying to fix a well (100 = destroyed)
    int timeUntilBrokenAgain = 7200; // The amount of time in seconds until a well breaks again (7200 = default 2 hours)
    bool enableWellTransferCholera = true; // If true, wells can transfer cholera to players when drinking from them
    int choleraChance = 100; // The chance of cholera being transferred to a player when drinking from a well (0-100)
    string messageCantDrink = "This well don't work, I wonder if it can be fixed? If not il have to find a river, stream or other natural water sources."; // Message displayed when a player tries to drink from the well
    string messageFixed = "It looks like this well is working for now...";  // Message displayed when a player fixes the well
    ref array<ref RepairableWell> RepairableWells = new ref array<ref RepairableWell>; // List of repairable wells
    

    // Loads the configuration file, or creates a new one if it doesn't exist
    void Load()
    {

        if (!GetGame().IsDedicatedServer())
			return;

        // Check if the config file exists
        if (FileExist(deadWellModFolder + deadWellConfigName))
        { 
            // Load the existing config file
            JsonFileLoader<DeadWellConfig>.JsonLoadFile(deadWellModFolder + deadWellConfigName, this);

            // If the version doesn't match, backup the old version
            if (ConfigVersion != CONFIG_VERSION)
            {
                JsonFileLoader<DeadWellConfig>.JsonSaveFile(deadWellModFolder + deadWellConfigName + "_old", this);
            }
            else
            {
                // If the config version matches, no further action is needed
                return;
            }
        }

        // If the config file doesn't exist, set default values
        RepairableWells.Clear();
        ConfigVersion = CONFIG_VERSION;

        // Save the default config
        Save();
    }

    // Saves the configuration to a file
    void Save()
    {

        if (!GetGame().IsDedicatedServer())
			return;
            
		// If the folder doesn't exist, create it
        if (!FileExist(deadWellModFolder))
        {
            MakeDirectory(deadWellModFolder);
        }

        // Save the config
        JsonFileLoader<DeadWellConfig>.JsonSaveFile(deadWellModFolder + deadWellConfigName, this);
    }

    int GetRepairableWellIndex(vector location)
    {
        for (int j = 0; j < RepairableWells.Count(); j++)
        {
            RepairableWell well = RepairableWells.Get(j);

            float loc_1 = location[0];
            float loc_2 = location[1];
            float loc_3 = location[2];

            float well_1 = well.Location[0];
            float well_2 = well.Location[1];
            float well_3 = well.Location[2];

            if (loc_1 > well_1 - 1 && loc_1 < well_1 + 1 && loc_2 > well_2 - 1 && loc_2 < well_2 + 1 && loc_3 > well_3 - 1 && loc_3 < well_3 + 1)
            {
                return j;
            }
        }

        return -1;
    }

    void SetWellRepaired(int index, vector location, bool repaired, bool forcesave)
    {
        int timeStamp = JMDate.Now(false).GetTimestamp() + timeUntilBrokenAgain;

        if (index <0 || index >= RepairableWells.Count())
        {
            RepairableWell newWell = new RepairableWell(location, true, timeStamp);
            RepairableWells.Insert(newWell);
        }
        else
        {
            if (repaired)
            {
                RepairableWells.Get(index).Repaired = true;
                RepairableWells.Get(index).BrokenTime = timeStamp;
            }
            else
            {
                RepairableWells.Get(index).Repaired = false;
                RepairableWells.Get(index).BrokenTime = 0;
            }
        }

        if (forcesave)
        Save();
    }
}

class RepairableWell
{
    vector Location;
    bool Indestructible = false;
    bool Repaired = false;
    int BrokenTime = 0;

    void RepairableWell(vector location, bool repaired, int brokenTime, bool indestructible = false)
    {
        Location = location;
        Repaired = repaired;
        BrokenTime = brokenTime;
        Indestructible = indestructible;
    }
};

// Reference to the global configuration object
ref DeadWellConfig m_DeathWellConfig;

// Function to access the configuration object
static DeadWellConfig GetDeadWellConfig()
{
    // Initialize the config only if it doesn't already exist and is running on a dedicated server
    if (!m_DeathWellConfig && GetGame().IsDedicatedServer())
    {
        Print("[DeadWellConfig] Initializing configuration...");
        m_DeathWellConfig = new DeadWellConfig;
        m_DeathWellConfig.Load();
    }

    return m_DeathWellConfig;
};