#ifndef CATEGORY
#define CATEGORY

// Entity/scene node category used to dispatch commands
namespace Category
{
    enum Type
    {
        None = 0,
        SceneAirLayer = 1 << 0,
        PlayerCharacter = 1 << 1,
        AlliedCharacter = 1 << 2,
        NeutralCharacter = 1 << 3,
        EnemyCharacter = 1 << 4,

        EveryCharacters = PlayerCharacter | AlliedCharacter | NeutralCharacter | EnemyCharacter,
        NonPlayableCharacters = AlliedCharacter | NeutralCharacter | EnemyCharacter,
        NonEnnemyCharacters = AlliedCharacter | NeutralCharacter,
    };
}

#endif // CATEGORY

