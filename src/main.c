#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>
#include <keypadc.h>

#define NUMBER_OF_WORDS 16

typedef enum
{
    PRGM_NORMAL,
    PRGM_RELOAD,
    PRGM_EXIT
} pgrm_state_t;

static const char* words[] =
{
    "DRAGON","COMPUTER","NOTE","CALCULATE","CASTLE","HARP","WORLD",
    "SEA","BOOK","WIZARD","TREE","PLANE","JUNGLE","TEMPLE","CACKE",
    "CHICKEN","DEVICE","BOTTLE","DOG","BEER","MOON","SPACESHIP","FIREWORK",
    "VOLCANO","STORM","POETRY","FLOWER","PYTHON","TIME","ICE","THUNDER",
    "FIRE","WITCH","HEL","BUILDING","BRIDGE","CHAIR","BIRD","ROCK","SUN",
    "STARS","ALIEN","UFO","WAND","KEY","LOCK","HOOK","HORSE","GOAT","RAIN",
    "ARROW","EYE","WATCH","JUMP","FISH","MASK","PENTAGRAM","SWORD","TOWN",
    "BABY","TURTLE","HUT","SKELETON","SHADOWS","MONSTER","SEARCH","CHEST",
    "SLEEP","GOLD","WRITER","LIGHT","DARKNESS","ANGLE","THOR","DEVIL","FOOD",
    "POISON","LABYRINTH","THIEF","CROWN","DWARF","WOLF","MARKET","PRINCESS",
    "CHURCH","DEAD","FISHER","SERPENT","KING","RAINBOW","SNOW","ARMOR",
    "FAIRY","BIKE","LOKI","BANDAGE","BLOOD","QUEEN","ISLAND","GAME",
    "OXYGEN","PLANT","SOAP","HERO","OIL","PAINTING","MUSIC"
};
int wordsresult[NUMBER_OF_WORDS];

/* This function sets the words on the screen */
static void woordeen(void)
{
    const uint24_t num_words = sizeof(words) / sizeof(const char*);
    uint8_t ypos = 40;
    uint24_t xpos = 1;
    uint8_t i;

    for(i = 0; i < NUMBER_OF_WORDS; ++i)
    {
        bool duplicate;
        uint8_t randd;

        do
        {
            uint8_t j;

            duplicate = false;
            randd = randInt(0, num_words - 1);

            for(j = 0; j < i; ++j)
            {
                if (wordsresult[j] == randd)
                {
                    duplicate = true;
                    break;
                }
            }
        } while (duplicate == true);

        wordsresult[i] = randd;
        gfx_PrintStringXY(words[randd], ypos, xpos);
        xpos += 15;
    }
}

static void setup_program(void)
{
    uint8_t ypos = 0;
    uint8_t i;

    gfx_Begin();
    gfx_SetColor(0);
    gfx_Line(200, 0, 200, 400);
    gfx_Line(319,0,319,400);
    gfx_HorizLine_NoClip(200,239,119);

    for(i = 0; i < NUMBER_OF_WORDS; ++i)
    {
        gfx_HorizLine_NoClip(200, ypos, 119);
        ypos += 15;
    }

    gfx_SetColor(255);
    woordeen();
}

/* This function checks what key press and does stuff based on that */
static pgrm_state_t scan_keys(uint8_t *num, uint8_t *entry)
{
    *entry = 0;

    kb_Scan();

    if (kb_IsDown(kb_KeyClear))
    {
        return PRGM_EXIT;
    }

    if (kb_IsDown(kb_KeyAlpha))
    {
        return PRGM_RELOAD;
    }

    if (kb_IsDown(kb_Key1))
    {
        *entry = 1;
    }
    if (kb_IsDown(kb_Key2))
    {
        *entry = 2;
    }
    if (kb_IsDown(kb_Key3))
    {
        *entry = 3;
    }
    if (kb_IsDown(kb_Key4))
    {
        *entry = 4;
    }
    if (kb_IsDown(kb_Key5))
    {
        *entry = 5;
    }
    if (kb_IsDown(kb_Key6))
    {
        *entry = 6;
    }
    if (kb_IsDown(kb_Key7))
    {
        *entry = 7;
    }
    if (kb_IsDown(kb_Key8))
    {
        *entry = 8;
    }
    if (kb_IsDown(kb_Key9))
    {
        *entry = 9;
    }

    if (kb_IsDown(kb_Key1))
    {
        delay(400);
        for (;;) {
            kb_Scan();
            if (kb_IsDown(kb_Key0))
            {
                *entry = 10;
                delay(300);
                break;
            }
            if (kb_IsDown(kb_Key1))
            {
                *entry = 11;
                delay(300);
                break;
            }
            if (kb_IsDown(kb_Key2))
            {
                *entry = 12;
                delay(300);
                break;
            }
            if (kb_IsDown(kb_Key3))
            {
                *entry = 13;
                delay(300);
                break;
            }
            if (kb_IsDown(kb_Key4))
            {
                *entry = 14;
                delay(300);
                break;
            }
            if (kb_IsDown(kb_Key5))
            {
                *entry = 15;
                delay(300);
                break;
            }
            if (kb_IsDown(kb_Key6))
            {
                *entry = 16;
                delay(300);
                break;
            }
            if (kb_IsDown(kb_KeyEnter))
            {
                *entry = 1;
                delay(300);
                break;
            }
        }
    }

    if (kb_IsDown(kb_KeyDown)) {
        (*num)++;
        if (*num == 17) {
            *num = 1;
        }
    }

    if (kb_IsDown(kb_KeyUp)) {
        (*num)--;
        if (*num == 0) {
            *num = 16;
        }
    }

    delay(120);

    return PRGM_NORMAL;
}

pgrm_state_t run_program(void)
{
    static uint8_t num = 1;
    static const uint8_t ypos_array[] =
    {
        0, 1, 16, 31, 46, 61, 76,
        91, 106, 121, 136, 151, 166, 181,
        196, 211, 226
    };
    uint8_t ypos;
    uint8_t entry;
    pgrm_state_t state;

    state = scan_keys(&num, &entry);

    /* This part places the word in the columns */
    if (entry != 0)
    {
        uint8_t wordpos = 2 + (entry - 1) * 15;
        const char *word = words[wordsresult[num - 1]];

        gfx_FillRectangle(202, wordpos, 98, 7);
        gfx_PrintStringXY(word, 202, wordpos);
    }

    gfx_FillRectangle(0, 0, 6, LCD_HEIGHT);
    ypos = ypos_array[num];
    gfx_PrintStringXY(">", 1, ypos);

    return state;
}

int main(void)
{
    srandom(rtc_Time());
    pgrm_state_t state;

    do
    {
        setup_program();
        do
        {
            state = run_program();
        } while(state == PRGM_NORMAL);
    } while (state != PRGM_EXIT);

    gfx_End();
    os_ClrHome();

    return 0;
}