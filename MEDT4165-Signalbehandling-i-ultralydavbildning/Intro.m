sig=randn(1000,1);
myFilter=hamming(50);

filtSig=filter(myFilter,1,sig);

figure(1),plot(sig);
figure(2),plot(myFilter,'k-x');
figure(3),plot(filtSig);


%% Fourier analysis
fs=10e3;
Nfft=length(sig);
freqTab=linspace(-0.5,0.5,Nfft+1)*fs; freqTab(end)=[];
fftSig=20*log10(abs(fftshift(fft(sig))));
fftFilter=20*log10(abs(fftshift(fft(myFilter))));
fftFiltSig=20*log10(abs(fftshift(fft(filtSig))));

figure(4),plot(freqTab,fftSig);
%%figure(5), hold off,plot(freqTab,fftFilter);
%%hold on,plot(freqTab,fftFiltSig,"r");

%%2D filtering
sig2D=randn(256,128);
figure(10),image(sig2D);
my2DFilt=ones(1,50);
myFiltSig2D=filter2(my2DFilt,sig2D);
figure(11),image(myFiltSig2D);

