#include "jazz.h"
#include "metal.h"
#include "rock.h"
#include "kpop.h"


int RockBand::play(MusicBand *other)
{
    if(const JazzBand* other_cast = dynamic_cast<const JazzBand*>(other))
    {
        int remaining_energy;
        double energy_const = 0.1;
        int score;
        double C = 0.8;

        score = (this->get_fan_count() + 0.1 * this->get_talent() * this->get_energy()) * C;
        remaining_energy = (this->get_energy() - this->get_energy() * energy_const);

        this->set_energy(remaining_energy);
        return score;

    }

    if(const MetalBand* other_cast = dynamic_cast<const MetalBand*>(other))
    {
        int remaining_energy;
        double energy_const = 0.1;
        int score;
        double C = 1.4;

        score = (this->get_fan_count() + 0.1 * this->get_talent() * this->get_energy()) * C;
        remaining_energy = (this->get_energy() - this->get_energy() * energy_const);

        this->set_energy(remaining_energy);
        return score;

    }

    if(const RockBand* other_cast = dynamic_cast<const RockBand*>(other))
    {
        int remaining_energy;
        double energy_const = 0.1;
        int score;
        double C = 1.0;

        score = (this->get_fan_count() + 0.1 * this->get_talent() * this->get_energy()) * C;
        remaining_energy = (this->get_energy() - this->get_energy() * energy_const);

        this->set_energy(remaining_energy);
        return score;

    }

    if(const KPopBand* other_cast = dynamic_cast<const KPopBand*>(other))
    {
        int remaining_energy;
        double energy_const = 0.1;
        int score;
        double C = 0.5;

        score = (this->get_fan_count() + 0.1 * this->get_talent() * this->get_energy()) * C;
        remaining_energy = (this->get_energy() - this->get_energy() * energy_const);

        this->set_energy(remaining_energy);
        return score;

    }
}

void RockBand::rehearse(void) 
{
    double energy_const = 0.1;
    double talent_const = 10.0;

    int remaining_energy;
    int remaining_talent;

    remaining_energy = (this->get_energy() - 0.5 * energy_const);
    remaining_talent = (this->get_talent() + talent_const);
}