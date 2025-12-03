#include <stdio.h>

int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets) {
    if (fuel <= 0) {
        printf("Mission failed! Out of fuel at Planet %d\n", planet);
        return 0;
    }
    
    if (planet > totalPlanets) {
        printf("Mission completed! Reached all %d planets with %d fuel remaining\n", totalPlanets, fuel);
        return 1;
    }
    
    printf("Planet %d: Fuel Remaining = %d", planet, fuel);
    
    fuel -= consumption;
    printf(" (After consumption: %d)", fuel);
    
    if (planet % 2 == 0) {
        fuel += recharge;
        printf(" (After gravitational recharge: %d)", fuel);
    }
    
    if (planet % 4 == 0) {
        fuel += solarBonus;
        printf(" (After solar recharge: %d)", fuel);
    }
    
    printf("\n");
    
    return calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main() {
    int initialFuel, totalPlanets;
    int consumption = 20;
    int recharge = 15;
    int solarBonus = 25;
    int choice;
    
    while (1) {
        printf("\n=== SPACECRAFT FUEL SIMULATION ===\n");
        printf("1. Run New Simulation\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter initial fuel: ");
                scanf("%d", &initialFuel);
                
                printf("Enter total number of planets: ");
                scanf("%d", &totalPlanets);
                
                printf("\n=== MISSION SIMULATION ===\n");
                printf("Initial Fuel: %d\n", initialFuel);
                printf("Consumption per planet: %d\n", consumption);
                printf("Gravitational Recharge: %d (every 2nd planet)\n", recharge);
                printf("Solar Bonus: %d (every 4th planet)\n", solarBonus);
                printf("Total Planets: %d\n\n", totalPlanets);
                
                int success = calculateFuel(initialFuel, consumption, recharge, solarBonus, 1, totalPlanets);
                
                if (success) {
                    printf("\nMission Status: SUCCESS\n");
                } else {
                    printf("\nMission Status: FAILED\n");
                }
                break;
                
            case 2:
                printf("Thank you for using the Spacecraft Fuel Simulator. Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
