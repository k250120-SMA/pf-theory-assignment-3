#include <stdio.h>

double calRepayment(double loan, double interestRate, int years) {
    if (years <= 0 || loan <= 0) {
        if (loan <= 0) {
            printf("Loan Fully Repaid\n");
        }
        if (years <= 0 && loan > 0) {
            printf("Year 0: Remaining Amount left = %.2f\n", loan);
        }
        return 0;
    }
    
    double interest = loan * interestRate / 100;
    double principal = loan / years;
    double annualInstallment = principal + interest;
    double remLoan = loan - principal;
    
    if (remLoan < 0) {
        remLoan = 0;
    }
    
    printf("Year %d: Payment = %.2f, Remaining loan = %.2f\n", years, annualInstallment, remLoan);
    
    return annualInstallment + calRepayment(remLoan, interestRate, years - 1);
}

double calRepayExtra(double loan, double interestRate, int years, double extraPay) {
    if (years <= 0 || loan <= 0) {
        if (loan <= 0) {
            printf("Loan Fully Repaid\n");
        }
        if (years <= 0 && loan > 0) {
            printf("Year 0: Remaining Amount left = %.2f\n", loan);
        }
        return 0;
    }
    
    double interest = loan * interestRate / 100;
    double principal = loan / years;
    
    if (principal + extraPay > loan) {
        principal = loan;
    } else {
        principal += extraPay;
    }
    
    double annualInstallment = principal + interest;
    double remainingPay = loan - principal;
    
    if (remainingPay < 0) {
        annualInstallment += remainingPay;
        remainingPay = 0;
    }
    
    printf("Year %d: Payment = %.2f, Remaining loan = %.2f\n", years, annualInstallment, remainingPay);
    
    return annualInstallment + calRepayExtra(remainingPay, interestRate, years - 1, extraPay);
}

int main() {
    double loan, Rate, extra;
    int years, choice;
    
    printf("Please enter your loan amount: ");
    scanf("%lf", &loan);
    
    printf("Please enter your interest rate: ");
    scanf("%lf", &Rate);
    
    printf("Please enter time in years: ");
    scanf("%d", &years);
    
    printf("\n1. Basic Repayment\n2. Repayment with Extra Payments\nEnter choice: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        double totalRepayment = calRepayment(loan, Rate, years);
        printf("Total repayment amount: %.2f\n", totalRepayment);
    } else if (choice == 2) {
        printf("Enter extra payment per year: ");
        scanf("%lf", &extra);
        double totalRepayment = calRepayExtra(loan, Rate, years, extra);
        printf("Total repayment amount: %.2f\n", totalRepayment);
    } else {
        printf("Invalid choice!\n");
    }
    
    return 0;
}
