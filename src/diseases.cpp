// v0.1 by gm (created)

#include "diseases.h"
#include "globals.h"
#include "soundlist.h"
#include "soundtotext.h"
#include "sound.h"
#include "valuelist.h"

#include <iostream>

// TODO: times!






// TODO: include Disease management in scheme (customization in scheme files)
//       => CREATE function that can set this values:

// TODO: Sounds bei Poops verbessern


int Diseases::m_times[DSE_NUMBER_OF] = { -1000 };

int Diseases::m_probablities[DSE_NUMBER_OF] = { -1000 };


Diseases::Diseases()
{
    init();
}

Diseases::~Diseases()
{
}

void
Diseases::init()
{
    // init static members only once:
    if (m_times[0] == -1000 || m_probablities[0] == -1000)
    {
        Globals g;
        for (int i = 0; i < DSE_NUMBER_OF; ++i)
        {
            m_times[i]        = g.values().get(static_cast < EnumValues > (VAL_DSE_TIME_MOLASSES + i));
            m_probablities[i] = g.values().get(static_cast < EnumValues > (VAL_DSE_PROB_MOLASSES + i));
        }
    }

    // deactivate all diseases:
    for (int i = 0; i < DSE_NUMBER_OF; ++i)
    {
        m_diseases[i] = 0;
    }
}

void
Diseases::infect (int number)
{
//    activate(DSE_POOPS);
//    play_sound(DSE_POOPS);

    if (number < 1)
        number = 1;

    EnumDiseases dse = DSE_MOLASSES;
    
    while (number--)
    {
        while (active(dse = choose_random()));    // choose a non-active disease

        activate (dse);
    }

    play_sound (dse);
}

int
Diseases::infected ()
{
    int cnt = 0;
    for (int i = 0; i < DSE_NUMBER_OF; ++i)
    {
        if (active(static_cast <EnumDiseases> (i)))
            ++cnt;
    }

    return cnt;
}

void
Diseases::cure_all()
{
    reset();
}

void
Diseases::reset()
{
    // deactivate all diseases:
    for (int i = 0; i < DSE_NUMBER_OF; ++i)
    {
        m_diseases[i] = 0;
    }
}

void
Diseases::activate(EnumDiseases which, bool bActivate)
{
    if (DSE_CRACKPOOPS == which)
    {
        m_diseases[DSE_CRACK] = bActivate;
        m_diseases[DSE_POOPS] = bActivate;
    }
    else
    {
        m_diseases[which] = bActivate;

        if (DSE_CRACK == which && active(DSE_MOLASSES))     // crack excludes molasses
            m_diseases[DSE_MOLASSES] = false;

        if (DSE_MOLASSES == which && active(DSE_CRACK))
            m_diseases[DSE_CRACK] = false;

        if (DSE_CONSTIPATION == which && active(DSE_POOPS))     // constipation excludes poops
            m_diseases[DSE_POOPS] = false;

        if (DSE_POOPS == which && active(DSE_CONSTIPATION))
            m_diseases[DSE_CONSTIPATION] = false;
    }
}

const bool
Diseases::active(EnumDiseases which) const
{
    return m_diseases[which];
}

void
Diseases::swap_ok()
{
    if (active(DSE_SWAP))
    {
        activate(DSE_SWAP, false);
    }
    else if (active(DSE_HYPERSWAP))
    {
        activate(DSE_HYPERSWAP, false);
    }
}

// TODO: F machen     
void
Diseases::play_sound (EnumDiseases which)
{
    Globals g;
    EnumSounds sound = SND_DISEASE;

    switch (which)
    {
    case DSE_MOLASSES:
        sound = SND_DISEASE_MOLASSES;
        break;

    case DSE_CRACK:
        sound = SND_DISEASE_CRACK;
        break;

    case DSE_CONSTIPATION:
        sound = SND_DISEASE_CONSTIPATION;
        break;

    case DSE_POOPS:
        sound = SND_DISEASE_POOPS;
        break;

    case DSE_SHORTFLAME:
        sound = SND_DISEASE_SHORTFLAME;
        break;

    case DSE_CRACKPOOPS:
        sound = SND_DISEASE_CRACKPOOPS;
        break;

    case DSE_SHORTFUZE:
        sound = SND_DISEASE_SHORTFUZE;
        break;

    case DSE_SWAP:
        sound = SND_DISEASE_SWAP;
        break;

    case DSE_REVERSED:
        sound = SND_DISEASE_REVERSED;
        break;

    case DSE_LEPROSY:
        sound = SND_DISEASE_LEPROSY;
        break;

    case DSE_INVISIBLE:
        sound = SND_DISEASE_INVISIBLE;
        break;

    case DSE_DUDS:
        sound = SND_DISEASE_DUDS;
        break;

    case DSE_HYPERSWAP:
        sound = SND_DISEASE_SWAP;
        break;

    case DSE_NUMBER_OF:
        cout << "Error in Diseases::play_sound (EnumDiseases which): which == DSE_NUMBER_OF" << endl;
        break;
    }
    
    string snd = g.soundlist().get_random_sound(sound);

    g.sound().play(snd);
    g.snd2txt().lookup(snd);
}

double
Diseases::speed_molasses() const
{
    return Globals::values().get(VAL_PLAYER_SPEED_MOLASSES);
}

double
Diseases::speed_crack() const
{
    static int add = rand()%Globals::values().get(VAL_PLAYER_SPEED_CRACK_ADD);
    static int cnt = 0;

    ++cnt;
    if (cnt > 200)     // TODO: wieder weg???
        add = rand()%Globals::values().get(VAL_PLAYER_SPEED_CRACK_ADD);

    return Globals::values().get(VAL_PLAYER_SPEED_CRACK) + add;
}

// TODO: test!!!
EnumDiseases
Diseases::choose_random()
{
    int sum = 0;    // sum of all probablity values
    int i = 0;

    for (i = 0; i < DSE_NUMBER_OF; ++i)
    {
        sum += m_probablities[i];
    }

    int rnd = rand() % sum;    // random number between 0..sum-1

    for (i = 0; i < DSE_NUMBER_OF; ++i)
    {
        rnd -= m_probablities[i];   // subtract probablity values until rnd < 0  =>  disease found!
        if (rnd < 0)
            return static_cast <EnumDiseases> (i);
    }

    cerr << "Error: Diseases::choose_random(): return std-value DSE_MOLASSES" << endl;
    return DSE_MOLASSES;
}

void
Diseases::debug_print_diseases()
{
    cout << "Diseases: ";
    if (active(DSE_MOLASSES)) cout << "MOLASSES, ";
    if (active(DSE_CRACK)) cout << "CRACK, ";       
    if (active(DSE_CONSTIPATION)) cout << "CONSTIPATION, ";
    if (active(DSE_POOPS)) cout << "POOPS, ";       
    if (active(DSE_SHORTFLAME)) cout << "SHORTFLAME, ";  
    if (active(DSE_CRACKPOOPS)) cout << "CRACKPOOPS, ";  
    if (active(DSE_SHORTFUZE)) cout << "SHORTFUZE, ";   
    if (active(DSE_SWAP)) cout << "SWAP, ";        
    if (active(DSE_REVERSED)) cout << "REVERSED, ";    
    if (active(DSE_LEPROSY)) cout << "LEPROSY, ";     
    if (active(DSE_INVISIBLE)) cout << "INVISIBLE, ";   
    if (active(DSE_DUDS)) cout << "DUDS, ";        
    if (active(DSE_HYPERSWAP)) cout << "HYPERSWAP, ";

    cout << endl;
}
