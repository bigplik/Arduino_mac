/*
pomysł na przechodzenie w power_down kilkukrotnie
i potem jeśli PPO2 nie będzie wyższe niż 0.25
przechodzenie w power_down z którego podwyższenie PPO2
spowoduje reset urządzenia np. poprzez podcięgnięcie
pinu reset do VCC (bądź masy jak nie zadziała)

zatem pierwsza pętla dodawałaby + 1 do licznika,
a po osiągnięciu odpowiedniej liczby urządzenie
przechodziłoby w stan power_down po którym
podniesienie PPO2 > 0.25 spodowowałoby:
- delay (10sek) w tym czasie należy przedmuchać reba Air
- i reset (podanie stanu wysokiego lub niskiego na pinRES

urządzenie powinno dać się skalibrować po przedmuchaniu reba AIR

jeśli natomiast PPO2 wzrośnie zanim urządzenie osiągnie
taki stan licznika który wprowadza go w stan power_down (reset)
wtedy urządznie sie wybudzi i działa dalej
*/
