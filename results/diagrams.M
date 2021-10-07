X = [1, 2, 4, 8, 16]
Y1 = [0.087932 0.278805 0.321334 0.352363 0.393207]
Y2 = [1.763913 5.074418 3.352160 3.126018 2.811118]
Y3 = [0.063627 0.192323 0.195200 0.212793 0.251401]
Y4 = [0.539022 1.406947 0.761468 0.422077 0.245278]
Y5 = [0.320220 0.799982 0.914551 0.908831 0.883939]

plot(X, Y1)
hold
plot(X, Y2)
plot(X, Y3)
plot(X, Y4)
plot(X, Y5)

title('OpenCilk')
xlabel('Number of Processors')
ylabel('Seconds to calculate')
legend('Belgium', 'Youtube', 'dble', 'cielskian', 'NACA')


Y1 = [0.087932 0.098410 0.096419 0.054796 0.018225]
Y2 = [0.063627 0.120479 0.095763 0.041331 0.022670]
Y3 = [0.539022 2.421233 2.001625 1.838767 1.505502]
Y4 = [0.320220 0.345864 0.205676 0.160665 0.081438]

plot(X, Y1)
hold
plot(X, Y2)
plot(X, Y3)
plot(X, Y4)

title('MPI')
xlabel('Number of Processors')
ylabel('Seconds to calculate')
legend('Belgium', 'dble', 'cielskian', 'NACA')

X = [1, 2, 4, 8, 16]
Y1 = [0.087932 0.024839 0.059776 0.073357 0.157198]
Y2 = [1.763913 0.535940 0.793653 0.815906 1.074799] 
Y3 = [0.063627 0.030184 0.029060 0.048248 0.160304]
Y4 = [0.539022 0.136520 0.133236 0.144958 0.262570]
Y5 = [0.320220 0.077520 0.148808 0.110132 0.445075]

plot(X, Y1)
hold
plot(X, Y2)
plot(X, Y3)
plot(X, Y4)
plot(X, Y5)

title('MPI-OpenCilk')
xlabel('Number of Processors')
ylabel('Seconds to calculate')
legend('Belgium', 'Youtube', 'dble', 'cielskian', 'NACA')