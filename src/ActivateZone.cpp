#include "ScriptMgr.h"

class ActivateCreature : public DataMap::Base
{
    public:
        ActivateCreature() {}
        ActivateCreature(bool isActive) : isActive(isActive) {}
        bool isActive = false;
};

class ActivateZoneAllCreature : public AllCreatureScript
{
    public:
        ActivateZoneAllCreature() : AllCreatureScript("ActivateZoneAllCreature") {}

        void OnAllCreatureUpdate(Creature* creature, uint32 diff) override
        {
            if (!sWorld->getBoolConfig(CONFIG_SET_ALL_CREATURES_WITH_WAYPOINT_MOVEMENT_ACTIVE))
            {
                if (creature->GetMapId() != 0 && creature->GetMapId() != 1 && creature->GetMapId() != 530 && creature->GetMapId() != 571)
                    return;

                if (creature->IsSummon() || creature->IsPet() || creature->IsHunterPet() || creature->IsTotem())
                    return;

                if (!creature->IsAlive())
                    return;

                if (sWorld->FindPlayerInZone(creature->GetZoneId()))
                {
                    if (!creature->CustomData.GetDefault<ActivateCreature>("ActivateCreature")->isActive)
                    {
                        creature->CustomData.Set("ActivateCreature", new ActivateCreature(creature->GetGUID()));
                        creature->setActive(true);
                        //LOG_INFO("server.loading", "Creature %s (zone: %u) is now active", creature->GetName().c_str(), creature->GetZoneId());
                    }
                }
                else
                {
                    if (creature->CustomData.GetDefault<ActivateCreature>("ActivateCreature")->isActive)
                    {
                        creature->CustomData.GetDefault<ActivateCreature>("ActivateCreature")->isActive = false;
                        creature->setActive(false);
                        //LOG_INFO("server.loading", "Creature %s (zone: %u) is no longer active", creature->GetName().c_str(), creature->GetZoneId());
                    }
                }
            }
        }
};

void AddActivateZonesScripts()
{
    new ActivateZoneAllCreature();
}
