import datetime


class Vonat:
    def __init__(self, sor):
        m = sor.split('\t')
        self.azon = int(m[0])
        self.allomas = int(m[1])
        self.ido = datetime.datetime(2020, 1, 1, int(m[2]), int(m[3]))
        self.status = str(m[4])
        self.varakozas = -1


def eltelt_ido_min(v1:Vonat, v2:Vonat):
    return int((v2.ido - v1.ido).total_seconds()) // 60


def main():
    # 1. feladat
    sr = open('vonat.txt', 'r', encoding='UTF8')
    vonatok = list()
    for i in sr.read().splitlines():
        akt_vonat = Vonat(i)
        # várakozási idő [min] meghatározása indulásoknál:
        if akt_vonat.status == 'I' and akt_vonat.allomas != 0: # Ha nem az első állomásról indul
            elozo_adatok = list(filter(lambda x: x.azon == akt_vonat.azon, vonatok))
            akt_vonat.varakozas =  eltelt_ido_min(elozo_adatok[-1], akt_vonat)
        vonatok.append(akt_vonat)
    sr.close()

    # 2. feladat
    vonatok_h = set()
    allomasok_h = set()
    for i in vonatok:
        vonatok_h.add(i.azon)
        allomasok_h.add(i.allomas)
    print(f'2. feladat\nAz állomások száma: {len(allomasok_h)}\nA vonatok száma: {len(vonatok_h)}')

    # 3. feladat
    rendezve_varakozas = sorted(vonatok, key=lambda x: x.varakozas)
    maxv = rendezve_varakozas[-1]
    print(f'3. feladat\nA(z) {maxv.azon}. vonat a(z) {maxv.allomas}. állomáson {maxv.varakozas} percet állt.')

    input_vonat = int(input('4. feladat\nAdja meg egy vonat azonosítóját! '))
    input_ido = input('Adjon meg egy időpontot (óra perc)! ')

    print('5. feladat')
    input_vonat_adatok = list(filter(lambda x: x.azon == input_vonat, vonatok))
    menetido = eltelt_ido_min(input_vonat_adatok[0], input_vonat_adatok[-1])
    if menetido == 142: # 2 * 60 + 22 = 142
        print(f'A(z) {input_vonat}. vonat útja pontosan az előírt ideig tartott.')
    elif menetido > 142:
        print(f'A(z) {input_vonat}. vonat útja {menetido - 142} perccel hosszabb volt az előírtnál.')
    else:
        print(f'A(z) {input_vonat}. vonat útja {142 - menetido} perccel rövidebb volt az előírtnál.')

    # 6. feladat
    sw = open(f'halad{input_vonat}.txt', 'w', encoding='UTF8')
    for i in input_vonat_adatok:
        if i.status == 'E':
            sw.write(f'{i.allomas}. állomás: {i.ido.hour}:{i.ido.minute}\n')
    sw.close()

    print('7. feladat')
    ido = datetime.datetime(2020, 1, 1, int(input_ido.split(' ')[0]), int(input_ido.split(' ')[1]))
    for i in vonatok_h:
        av = list(filter(lambda x: x.azon == i, vonatok)) # aktuális vonat
        for j in range(1, len(av)):
            if av[j - 1].status == 'I': # j - 1 indulási idő, j a következő érkezés ideje
                if av[j - 1].ido <= ido < av[j].ido:
                    print(f'A(z) {av[j].azon}. vonat a {av[j-1].allomas}. és a {av[j].allomas}. állomás között járt.')
            else:
                if av[j - 1].ido <= ido < av[j].ido: # j - 1 érkezési idő, j a következő indulás ideje
                    print(f'A(z) {av[j].azon}. vonat a {av[j].allomas}. állomáson állt.')


if __name__ == '__main__':
    main()
