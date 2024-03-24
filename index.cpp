#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int size;
    double BFL_p, BFL_M_0, BFL_M_C,BFL_M;
    vector<double> c;
    vector<double> n;
    vector<double> d;
    
    cout << "Enter the number of surfaces in the lens system: ";
    cin >> size;
    
    // Saving Radius of Curvature in Vector
    for (int i = 0; i < size; i++) {
        double curvature;
        cout << "Enter Curvature for " << i + 1 << "th surface: ";
        cin >> curvature;
        c.push_back(curvature);
    }
    
    // Saving Refractive Index and Distance in Vectors
    n.push_back(1); // First Surface is always air
    for (int i = 1; i < size; i++) {
        double distance, RI;
        cout << "Enter Distance between " << i << "th and " << i + 1 << "th surface: ";
        cin >> distance;
        d.push_back(distance);
        
        cout << "Enter RI between " << i << "th and " << i + 1 << "th surface: ";
        cin >> RI;
        n.push_back(RI);
    }
    n.push_back(1); // Last Surface is also air
    d.push_back(0); // Distance between last surface and air is 0
    
    double y = 2.000;
    double u = 0.00;
    
    // Back Focal Length for Paraxial Ray
    cout << "Determining for paraxial ray.\n";
    for (int a = 0; a < size; a++) {
        double i = y * c[a] + u;
        double i_ = (n[a] / n[a + 1]) * i;
        double u_ = u - i + i_;
        double y2 = y + d[a] * u_;
        
        if (a == (size - 1)) {
            double u0 = u_;
            double y0 = y;
            BFL_p = y0 / u0;
        }
        cout<<"Data Generated for "<<a+1<<"th plane:"<<endl;
        cout<<"y="<<y<<endl;
        cout<<"y2="<<y2<<endl;
        cout<<"i="<<i<<endl;
        cout<<"i'="<<i_<<endl;
        cout<<"u="<<u<<endl;
        cout<<"u'="<<u_<<endl;
        u = u_;
        y = y2;
    }
    
    cout << "In case of Paraxial, Back Focal Length is: " << BFL_p << endl;
    
   
    double Q = 3.172;
    double U = 0;
    
    for (int z = 0; z < size; z++) {
        cout << "for " << (z + 1) << "th surface:" << endl;
        if (c[z] == 0) { // If curvature is zero, use plain surface formula
            double I = asin(Q + sin(U));
            double I_ = asin((n[z] / n[z + 1]) * sin(I));
            double U_ = asin((n[z] / n[z + 1]) * sin(U));
            double Q_ = (cos(U_) / cos(U)) * Q;
            double Q2 = Q + d[z] * sin(U_);

            if (z == (size - 1)) {
                double q0 = Q_;
                double sin_U_0 = sin(U_);
                BFL_M_0 = -q0 / sin_U_0;
                cout << "Back Focal Length in case of Marginal ray (Plain surface formula): " << BFL_M_0 << endl;
            }

            cout<<"Q= "<<Q<<endl;
            cout<<"Q'= "<<Q_<<endl;
            cout<<"I= "<<I*(180/M_PI)<<endl;
            cout<<"sin(I)= "<<sin(I)<<endl;
            cout<<"I'= "<<I_*(180/M_PI)<<endl;
            cout<<"sinI'= "<<sin(I_)<<endl;
            cout<<"U= "<<U*(180/M_PI)<<endl;
            cout<<"sinU= "<<sin(U)<<endl;
            cout<<"U'= "<<U_*(180/M_PI)<<endl;
            cout<<"sinU'= "<<sin(U_)<<endl;
            Q = Q2;
            U = U_;
        } else { // Otherwise, use curved surface formula
            double I = asin(Q * c[z] + sin(U));
            double I_ = asin((n[z] / n[z + 1]) * sin(I));
            double U_ = U + I_ - I;
            double Q_ = (1 / c[z]) * (sin(I_) - sin(U_));
            double Q2 = Q + d[z] * sin(U_);

            if (z == (size - 1)) {
                double q0 = Q_;
                double sin_U_0 = sin(U_);
                BFL_M_C = -q0 / sin_U_0;
                cout << "Back Focal Length in case of Marginal ray (Curved surface formula): " << BFL_M_C << endl;
            }

            cout<<"Q= "<<Q<<endl;
            cout<<"Q'= "<<Q_<<endl;
            cout<<"I= "<<I*(180/M_PI)<<endl;
            cout<<"sin(I)= "<<sin(I)<<endl;
            cout<<"I'= "<<I_*(180/M_PI)<<endl;
            cout<<"sinI'= "<<sin(I_)<<endl;
            cout<<"U= "<<U*(180/M_PI)<<endl;
            cout<<"sinU= "<<sin(U)<<endl;
            cout<<"U'= "<<U_*(180/M_PI)<<endl;
            cout<<"sinU'= "<<sin(U_)<<endl;
            Q = Q2;
            U = U_;
        }
    }
    if(c[size-1]==0){
        BFL_M= BFL_M_0;
    } else{
        BFL_M= BFL_M_C;
    }
    double SA= BFL_M-BFL_p;
    cout<<"Spherical Abberation of the lens system is: "<<SA<<endl;
    return 0;
}
