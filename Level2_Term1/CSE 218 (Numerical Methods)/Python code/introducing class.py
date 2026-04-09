class point:
    def __init__(self,x,y):
        self.x=x
        self.y=y

    def distance(self,rhs):
        return((self.x-rhs.x)**2+(self.y-rhs.y)**2)

    p1=point(2,4)
    p2=point(4,6)
    
