/*
5) Toteuta ohjelma, joka laskee paljonko saadaan kilometrikorvausta
275 kilometriltä, kun yhdestä kilometristä saatava korvaus on 0,44€.
Ohjelma tulostaa vastauksen näytölle.
 */
package KT01;
 
public class T05 {
   public static void main (String[] args) {
    double matka = 275;
    double korvauspkm = 0.44;
    double korvausyht = matka * korvauspkm;
    System.out.printf("Kilometrikorvaus: " + korvausyht);
    }   
}
