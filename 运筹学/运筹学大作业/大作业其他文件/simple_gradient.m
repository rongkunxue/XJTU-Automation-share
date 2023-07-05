error=10^-6; 
x0=[0,0]; 
syms x1 x2
f=2*x1^2+2*x2^2-2*x1*x2-4*x1-6*x2; 
AB=[1,1,1,0;1,5,0,1]; B=[1,0;0,1];N=[1,1;1,5];
[a,b]=size(x0);
initial_gradient=gradient_my(f,x0,b); 
norm=0;
normO=0; 
syms t; 
A=[]; 
    rN=[initial_gradient(1),initial_gradient(2)]
    pN=-rN; 
    pB=-[pN(1)+pN(2),-pN(1)-5*pN(2)];
    search direction=[pN pB]
for i=1:4
    norm0=normO+(search_direction(i))^2
end

    tmax=5/34; 
    x00=[0,0,2,-5]; 
    x=x00+t*search_direction; 
    xx=[x(1),x(2)];
    f_step=subs(f,findsym(f),xx);
    F=diff(f_step,t); 
    solve(F,t)
    x_1=x00+tmax*search_direction
    norm=normO;
    k=1;
    HS2=[];
while(norm>error && k<3)
    x_11=[x_1(1),x_1(2)]
    gradient=gradient_my(f,x_11,b)
    rN=-[1.25*gradient(1) ,0.25*gradient(2)] 
    pN=-[rN(1)*x_1(3) ,rN(2)*x_1(4)]
    pB=-[1.25*pN(1) ,0.25*pN(2) ];
    new_direction=[pB pN];
    norm=0 ;
    TT=[];
    tmax=1 ;
    for i=1:4
        norm=norm+(new_direction(i))^2
    end
    for j=1:4 
        if (new_direction(j)<0)
            T(j)= new_direction(j)
        else
        T(j)=0;
        end
        if (T(j)<0)
        TT-abs([TT, (x_1(j)/T(j))])
        end
        j=j+1;
    end
    
    n=size (TT) ;
    for uk=1:n
        if (tmax> TT(uk) )
            tmax=TT (uk)
            n=n+1 ;
        end
    end
    x=x_1+t*new_direction;
    Xx=[x(1),X(2)];
    f_step=subs(f,findsym(f),Xx) ;
    F=diff(f_step,t) ;
    solve(F,t) ;
    t0=tmax;
    
    x_2=x_1+0.18*new_direction
    A=[A;x_2];
    normO=norm;
    search_direction=new_direction
    x_1=x_2;
    xx2=[x_2(1) ,x_2(1)];
    
    Y=subs(f,findsym(f),xx2) ;
    HSZ=[HSZ;Y]
    k=k+1;
    end
    k
    x_2
    norm

