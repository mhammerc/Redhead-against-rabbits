# Coding Conventions

You must follow these rules.

#### Includes

The include hierarchy must be as follow :
    
    [Include your owns files]

    [Include every non standard libs (such as SFML)]

    [Include every standard libs (such as <string>)]

#### If, while, for and others

You must always put braces (`{}`) even if there is only one line of code.

Bad :

    if(true)
        go();

Good :

    if(true)
    {
        go();
    }

You must apply this rule except if the block is not alone and well surrounded. Example :

    if(isAllied())
        return Category::AlliedCharacter;
    else if(isEnemy())
        return Category::EnemyCharacter;
    else
        return Category::NeutralCharacter;

