fs = 100;
f1 = 5; a1 = 0.02; %frequency and amplitude of signal component 1
f2 = 45; a2 = 0.02; %frequency and amplitude of signal component 2
n1 = 0.0002; %noise amplitude
t = 0:1/fs:1;
s = a1*cos( 2*pi*f1*t) + a2*cos( 2*pi*f2*t) + n1*randn( size( t) );

fftS=20*log10(abs(fftshift(fft(s))));
Nfft=length(s)
f=linspace(-0.5,0.5,Nfft+1); f(end)=[]

figure(1); 
subplot(1,2,1); plot(t,s);
xlabel("Time"); ylabel("Signal intensity"); title("Signal in time");
subplot(1,2,2); plot(f,fftS); 
xlabel("Normalized frequency"); ylabel("Fourier power"); title("Power spectrum");

A1=fir1(22,0.5,"low")
A2=fir1(22,0.5,"high")

fftA1=20*log10(abs(fftshift(fft(A1, Nfft))));
fftA2=20*log10(abs(fftshift(fft(A2, Nfft))));

figure(2);
hold off; plot(f,fftS); 
hold on; plot(f,fftA1); 
hold on; plot(f,fftA2);
xlabel("Normalized frequency"); ylabel("Fourier power"); title("Power spectrum");


filtLowS=filter(A1, 1, s)
filtHighS=filter(A2, 1, s)

figure(3);
subplot(1,2,1); plot(filtLowS);
xlabel("Time"); ylabel("Signal intensity"); title("Lowpass filtered");
subplot(1,2,2); plot(filtHighS);
xlabel("Time"); ylabel("Signal intensity"); title("Highpass filtered")

downS=s(1:2:end);
downT=t(1:2:end);
fftDownS=20*log10(abs(fftshift(fft(downS))));
downNfft=length(downS)
downF=linspace(-0.5,0.5,downNfft+1); downF(end)=[]

figure(4);
subplot(1,2,1); plot(downT,downS);
xlabel("Time"); ylabel("Signal intensity"); title("Downsampled signal");
subplot(1,2,2); plot(downF,fftDownS);
xlabel("Normalized frequency"); ylabel("Fourier intensity"); title("Downsampled power spectrum");



