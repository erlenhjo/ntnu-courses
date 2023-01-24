Nfft=length(sn);
fftSn=20*log10(abs(fftshift(fft(sn))));
fftS=20*log10(abs(fftshift(fft(s))));
f=linspace(-0.5,0.5, Nfft+1); f(end)=[];

filt=fir1(100,0.1,"low");
fftFilt=20*log10(abs(fftshift(fft(filt,Nfft))));

figure(6);
subplot(1,2,1);
hold off; plot(f,fftS);
hold on; plot(f,fftFilt);
xlabel("Frequency"); ylabel("Fourier power"); title("Power spectrum w/o noise");
subplot(1,2,2); plot(f,fftSn);
xlabel("Frequency"); ylabel("Fourier power"); title("Power spectrum w noise");


%filtSig=filter(filt,1,sig);
filtSn=filter2(filt,sn);


figure(5); 
subplot(1,2,1); hold off; plot(t,s);
hold on; plot(t,filtSig)
xlabel("Time"); ylabel("Signal intensity"); title("Without noise");
subplot(1,2,2);plot(t,sn);
xlabel("Time"); ylabel("Signal intensity"); title("With noise");


errorInit=mean((sn-s).^2)
errorFilt=mean((filtSn-s).^2)

ratio=20*log10(errorInit/errorFilt)


