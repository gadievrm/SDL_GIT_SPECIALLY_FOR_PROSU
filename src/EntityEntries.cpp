#include "EntityEntries.h"
#include "Player.h"
#include "Gem.h"

std::unordered_map<std::string, TEntityEntry> gEnts = {
    { CPlayer::CLASS_NAME, { .load = CPlayer::Load, .save = CPlayer::Save } },
    {    CGem::CLASS_NAME, { .load =    CGem::Load, .save =    CGem::Save } }
};