#include "ScriptMgr.h"

class ActivateZone : public AllCreatureScript
{
    public:
        ActivateZone() : AllCreatureScript("ActivateZone") {}

        void OnAllCreatureUpdate(Creature* creature, uint32 diff) override
        {
            if (!sWorld->getBoolConfig(CONFIG_SET_ALL_CREATURES_WITH_WAYPOINT_MOVEMENT_ACTIVE) && sWorld->getBoolConfig(CONFIG_PRELOAD_ALL_NON_INSTANCED_MAP_GRIDS))
            {
                if (creature->GetMapId() != 0 && creature->GetMapId() != 1 && creature->GetMapId() != 530 && creature->GetMapId() != 571)
                    return;

                if (creature->IsSummon() || creature->IsPet() || creature->IsHunterPet() || creature->IsTotem())
                    return;

                CreatureAddon const* cainfo = creature->GetCreatureAddon();

                time += diff;

                if (sWorld->FindPlayerInZone(creature->GetZoneId()))
                {
                    if (time > delay)
                    {
                        if (cainfo->path_id != 0)
                            creature->setActive(true);

                        time = 0;
                    }
                }
                else
                {
                    if (time > delay)
                    {
                        if (cainfo->path_id != 0)
                            creature->setActive(false);

                        time = 0;
                    }
                }
            }
        }

    private:
        uint32 time = 0;
        uint32 delay = 1 * (60 * 1000);
};

void AddActivateZonesScripts()
{
    new ActivateZone();
}
