struct ApricornTree
{
    u8 minimum;
    u8 maximum;
    enum ApricornType apricornType;
};

const struct ApricornTree gApricornTrees[APRICORN_TREE_COUNT] =
{
    [APRICORN_TREE_NONE] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_RED,
    },
    [APRICORN_TREE_ROUTE29_GREEN] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_GREEN,
    },
    [APRICORN_TREE_ROUTE30_GREEN] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_GREEN,
    },
    [APRICORN_TREE_ROUTE30_PINK] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_PINK,
    },
    [APRICORN_TREE_ROUTE31_BLACK] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_BLACK,
    },
    [APRICORN_TREE_ROUTE33_PINK] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_PINK,
    },
    [APRICORN_TREE_ROUTE35_GREEN] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_GREEN,
    },
    [APRICORN_TREE_ROUTE36_BLUE] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_BLUE,
    },
    [APRICORN_TREE_ROUTE37_BLUE] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_BLUE,
    },
    [APRICORN_TREE_ROUTE38_WHITE] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_WHITE,
    },
    [APRICORN_TREE_ROUTE39_GREEN] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_GREEN,
    },
    [APRICORN_TREE_ROUTE42_YELLOW] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_YELLOW,
    },
    [APRICORN_TREE_ROUTE43_BLACK] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_BLACK,
    },
    [APRICORN_TREE_ROUTE44_RED] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_RED,
    },
    [APRICORN_TREE_ROUTE45_GREEN] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_GREEN,
    },
    [APRICORN_TREE_ROUTE46_GREEN] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_GREEN,
    },
    [APRICORN_TREE_AZALEA_WHITE] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_WHITE,
    },
    [APRICORN_TREE_VIOLET_YELLOW] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_YELLOW,
    },
};
