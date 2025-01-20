#!/usr/bin/env python

Rank = ['2', '3', '4','5', '6', \
        '7', '8', '9', '10', 'J', 'Q', 'K', 'A']
Suit = ["Spade", "Heart", "Diamond", "Club"]

All_Cards = [suit+rank for suit in Suit for rank in Rank] 
Card_Symbol = [suit[0]+rank for suit in Suit for rank in Rank] 
Suit_Dictionary = {s[0]:s for s in Suit}

def cmp_card_rank(x, y):
     (x_pos, y_pos) = (Rank.index(x), Rank.index(y))
     if (x_pos > y_pos):
         return 1
     elif (x_pos == y_pos):
         return 0
     else:
         return -1

class card(object):
    def __init__(self,suit,rank):
        if rank in Rank:
            self.rank = rank
        if suit in Suit:
            self.suit = suit 
        elif suit in Suit_Dictionary.keys():
            self.suit = Suit_Dictionary[suit]
    def short_symbol(self): # a class method
        return Card_Symbol[Suit.index(self.suit)*13+Rank.index(self.rank)]
    def full_name(self): # a class method
        return All_Cards[Suit.index(self.suit)*13+Rank.index(self.rank)]
    def __repr__(self): # overloads printing
        return 'Card %s %s' % (self.suit, self.rank)

class hand(object):
    def __init__(self,name='Generic'):
        self.name = name
        self.cardlist = []
    def addcard(self,one):
        if isinstance(one, card):
            self.cardlist.append(one)
    def __repr__(self):
        str = 'This is a hand named %s\n' % self.name
        str = str + 'It has %d card(s)\n' % len(self.cardlist)
        for card in self.cardlist:
            str = str + `card` + '\n' #apostrophe, not single quote
        return str

class flush_hand(hand):
    def __init__(self,name="Name unassigned", suit="Suit unassigned"):
        self.suit = suit
#        super() not working well, directly extend hand.__init__()
#        super(flush_hand, self).__init__(name)
        hand.__init__(self,name)
    def changesuit(self, suit):
        if suit in Suit:
            self.suit = suit 
        elif suit in Suit_Dictionary.keys():
            self.suit = Suit_Dictionary[suit]
        else:
            return
        for cd in self.cardlist:
            cd.suit = self.suit
    def __repr__(self):
        str = 'Flush Hand!\n'
        str = str + 'This is a %s flush hand named %s\n' %\
        (self.suit, self.name)
        str = str + 'It has %d card(s)\n' % len(self.cardlist)
        str = str + 'Show all card(s) in a row.\n'
        cardrow = []
        for card in self.cardlist:
            cardrow.append(card.short_symbol()[1:])
        cardrow.sort(cmp_card_rank) #compare result to without cmp funtion
        str = str + `cardrow` + '\n'
        return str


c1=card('C', '5')
c2=card('C', '9')
c3=card('S', 'J')

h=hand(name="Not good hand")
h.addcard(c1)
h.addcard(c2)
h.addcard(c3)
print h

fh=flush_hand(name="Flush Demo", suit='Heart')
fh.addcard(card("H","J"))
fh.addcard(card("H","10"))
fh.addcard(card("H","4"))
fh.addcard(card("H","9"))
fh.addcard(card("H","A"))
print fh

fh.changesuit("Diamond")
print fh

