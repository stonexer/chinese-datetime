All:lib WX CG ReadAll Tic age SaveMoon filetest rm cp mv test re clock Rmemu Alarm bk show kill new cfg SaveQQ PowerOn S R ShutDwn IE Lock B64 Mail chat A ReTick ip Install BD BTM Enable 1 2 Cal
lib:libbase.a
ReadAll:Read ReadMem SetReg SetRight Srd InstallRead Uninstall
ora:rjfind
Tic:Ticker
re:Create_Program_link rebuild

soupath=D:\Moontalk\Programs\Code
binpath=D:\Moontalk\Programs\Bin
libpath=D:\Moontalk\Programs\Lib
Incpath=D:\Moontalk\Programs\Include
bookpath=D:\Moontalk\Programs\ReadBook

orainclude=C:\app\Administrator\product\11.1.0\db_1\precomp\public
oralib=C:\app\Administrator\product\11.1.0\db_1\precomp\LIB

MkSock=-lwsock32
MkMusic=-lwinmm
MkBaseOpt=-I$(Incpath) -IC:\MinGW\include -L$(libpath) -LC:\MinGW\lib -lbase $(MkSock)
MkOraPcOpt=parse=none INCLUDE=$(orainclude) CHAR_MAP=STRING DBMS=NATI
MkOraCOpt=-I$(orainclude) -L$(oralib) -lorasql11

GG=gcc -O2 -o
GC=gcc -O2 -c
GGW=gcc -mwindows -O2 -o

filetest:filetest.c
	$(GG) $(binpath)\filetest $(soupath)\filetest.c
show:show.c
	$(GG) $(binpath)\show $(soupath)\show.c
kill:kill.c
	$(GG) $(binpath)\kill $(soupath)\kill.c $(MkBaseOpt)
libbase.a:base.o des.o mail.o Lunar.o
	ar r $(libpath)\libbase.a $(soupath)\base.o $(soupath)\des.o $(soupath)\mail.o $(soupath)\Lunar.o
	rm -f *.o
Lunar.o:Lunar.c
	$(GC) $(soupath)\Lunar.c $(MkBaseOpt)
mail.o:mail.c
	$(GC) $(soupath)\mail.c $(MkBaseOpt)
des.o:des.c
	$(GC) $(soupath)\des.c $(MkBaseOpt)
base.o:base.c
	$(GC) $(soupath)\base.c $(MkBaseOpt)
test:test.c
	$(GG) $(binpath)\test $(soupath)\test.c $(MkBaseOpt) $(MkMusic) -g
Rmemu:Rmemu.c
	$(GGW) $(binpath)\Rmemu $(soupath)\Rmemu.c $(MkBaseOpt)
Srd:Srd.c
	$(GGW) $(binpath)\Srd $(soupath)\Srd.c $(MkBaseOpt)
Read:ReadKey.c
	$(GG) $(bookpath)\Read $(soupath)\ReadKey.c $(MkBaseOpt)
ReadMem:ReadMem.c
	$(GG) $(binpath)\ReadMem $(soupath)\ReadMem.c $(MkBaseOpt)
SetReg:SetReg.c
	$(GGW) $(bookpath)\SetReg $(soupath)\SetReg.c $(MkBaseOpt)
SetRight:SetRight.c
	$(GGW) $(bookpath)\SetRight $(soupath)\SetRight.c $(MkBaseOpt)
InstallRead:InstallRead.c
	$(GG) $(bookpath)\InstallRead $(soupath)\InstallRead.c $(MkBaseOpt)
Uninstall:Uninstall.c
	$(GG) $(bookpath)\Uninstall $(soupath)\Uninstall.c $(MkBaseOpt)
B64:B64.c
	$(GG) $(binpath)\B64 $(soupath)\B64.c $(MkBaseOpt)
PowerOn:Poweron.c
	$(GGW) $(binpath)\PowerOn $(soupath)\Poweron.c $(MkBaseOpt)
Create_Program_link:create.c
	$(GG) $(binpath)\Create_Program_link $(soupath)\create.c $(MkBaseOpt)
rebuild:rebuild.c
	$(GGW) $(binpath)\rebuild $(soupath)\rebuild.c $(MkBaseOpt)
bk:bk.c
	$(GG) $(binpath)\bk $(soupath)\bk.c $(MkBaseOpt)
new:new.c
	$(GG) $(binpath)\new $(soupath)\new.c $(MkBaseOpt)
Ticker:Ticker.c
	$(GGW) $(binpath)\Ticker $(soupath)\Ticker.c $(MkBaseOpt)
ReTick:ReTick.c
	$(GGW) $(binpath)\ReTick $(soupath)\ReTick.c $(MkBaseOpt)
clock:clock.c
	$(GGW) $(binpath)\clock $(soupath)\clock.c $(MkBaseOpt) $(MkMusic)
rjfind:rjfind.c
	$(GG) $(binpath)\rjfind $(soupath)\rjfind.c $(MkOraCOpt) $(MkBaseOpt)
	rm -f $(soupath)\rjfind.c
rjfind.c:rjfind.pc
	proc iname=$(soupath)\rjfind.pc $(MkOraPcOpt)
cfg:cfg.c
	$(GG) $(binpath)\cfg $(soupath)\cfg.c $(MkBaseOpt)
Alarm:Alarm.c
	$(GGW) $(binpath)\Alarm $(soupath)\Alarm.c $(MkBaseOpt) $(MkMusic)
SaveQQ:SaveQQ.c
	$(GGW) $(binpath)\SaveQQ $(soupath)\SaveQQ.c $(MkBaseOpt)
SaveMoon:SaveMoon.c
	$(GGW) $(binpath)\SaveMoon $(soupath)\SaveMoon.c $(MkBaseOpt)
S:S.c
	$(GGW) $(binpath)\S $(soupath)\S.c $(MkBaseOpt)
R:R.c
	$(GGW) $(binpath)\R $(soupath)\R.c $(MkBaseOpt)
A:A.c
	$(GGW) $(binpath)\A $(soupath)\A.c $(MkBaseOpt)
ShutDwn:ShutDwn.c
	$(GGW) $(binpath)\ShutDwn $(soupath)\ShutDwn.c $(MkBaseOpt)
Lock:Lock.c
	$(GGW) $(binpath)\Lock $(soupath)\Lock.c $(MkBaseOpt)
Mail:mailsend.c
	$(GG) $(binpath)\Mail $(soupath)\mailsend.c $(MkBaseOpt)
chat:chat.c
	$(GGW) $(binpath)\chat $(soupath)\chat.c $(MkBaseOpt)
ip:ip.c
	$(GG) $(binpath)\ip $(soupath)\ip.c $(MkBaseOpt)
cp:cp.c
	$(GG) $(binpath)\cp $(soupath)\cp.c $(MkBaseOpt)
rm:rm.c
	$(GG) $(binpath)\rm $(soupath)\rm.c $(MkBaseOpt)
mv:mv.c
	$(GG) $(binpath)\mv $(soupath)\mv.c $(MkBaseOpt)
Install:Install.c
	$(GG) $(binpath)\Install $(soupath)\Install.c $(MkBaseOpt)
BD:bd.c
	$(GGW) $(binpath)\BD $(soupath)\bd.c $(MkBaseOpt)
IE:ie.c
	$(GGW) $(binpath)\IE $(soupath)\ie.c $(MkBaseOpt)
BTM:btm.c
	$(GG) $(binpath)\BTM $(soupath)\BTM.c $(MkBaseOpt)
Enable:enable.c
	$(GGW) $(binpath)\Enable $(soupath)\enable.c $(MkBaseOpt)
1:1.c
	$(GG) $(binpath)\1 $(soupath)\1.c $(MkBaseOpt)
2:2.c
	$(GG) $(binpath)\2 $(soupath)\2.c $(MkBaseOpt)
Age:age.c
	$(GG) $(binpath)\Age $(soupath)\age.c $(MkBaseOpt)
Cal:Cal.c
	$(GG) $(binpath)\Cal $(soupath)\Cal.c $(MkBaseOpt)
CG:ChengGu.c
	$(GG) $(binpath)\CG $(soupath)\ChengGu.c $(MkBaseOpt)
WX:wuxing.c
	$(GG) $(binpath)\WX $(soupath)\wuxing.c $(MkBaseOpt)
