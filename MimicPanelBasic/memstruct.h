/*
Please do not alter these unless you are an LCC developer, as change may break the code.
*/


#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

//#define ROUTE(i) PEID(inputs[i].routeA), PEID(inputs[i].routeB), PEID(inputs[i].routeC), PEID(inputs[i].routeD), PEID(inputs[i].routeE), PEID(inputs[i].routeF)
#define ROUTE(i) PEID(inputs[i].to[0]), PEID(inputs[i].to[1]),PEID(inputs[i].to[2]),PEID(inputs[i].to[3]),PEID(inputs[i].to[4]),PEID(inputs[i].to[5])

#define _ROUTEEID_0 
#define _ROUTEEID_1 ROUTE(0)
#define _ROUTEEID_2 _ROUTEEID_1, ROUTE(1)
#define _ROUTEEID_3 _ROUTEEID_2, ROUTE(2)
#define _ROUTEEID_4 _ROUTEEID_3, ROUTE(3)
#define _ROUTEEID_5 _ROUTEEID_4, ROUTE(4)
#define _ROUTEEID_6 _ROUTEEID_5, ROUTE(5)
#define _ROUTEEID_7 _ROUTEEID_6, ROUTE(6)
#define _ROUTEEID_8 _ROUTEEID_7, ROUTE(7)
#define _ROUTEEID_9 _ROUTEEID_8, ROUTE(8)
#define _ROUTEEID_10 _ROUTEEID_9, ROUTE(9)
#define _ROUTEEID_11 _ROUTEEID_10, ROUTE(10)
#define _ROUTEEID_12 _ROUTEEID_11, ROUTE(11)
#define _ROUTEEID_13 _ROUTEEID_12, ROUTE(12)
#define _ROUTEEID_14 _ROUTEEID_13, ROUTE(13)
#define _ROUTEEID_15 _ROUTEEID_14, ROUTE(14)
#define _ROUTEEID_16 _ROUTEEID_15, ROUTE(15)
#define _ROUTEEID_17 _ROUTEEID_16, ROUTE(16)
#define _ROUTEEID_18 _ROUTEEID_17, ROUTE(17)
#define _ROUTEEID_19 _ROUTEEID_18, ROUTE(18)
#define _ROUTEEID_20 _ROUTEEID_19, ROUTE(19)
#define _ROUTEEID_21 _ROUTEEID_20, ROUTE(20)
#define _ROUTEEID_22 _ROUTEEID_21, ROUTE(21)
#define _ROUTEEID_23 _ROUTEEID_22, ROUTE(22)
#define _ROUTEEID_24 _ROUTEEID_23, ROUTE(23)
#define _ROUTEEID_25 _ROUTEEID_24, ROUTE(24)
#define _ROUTEEID_26 _ROUTEEID_25, ROUTE(25)
#define _ROUTEEID_27 _ROUTEEID_26, ROUTE(26)
#define _ROUTEEID_28 _ROUTEEID_27, ROUTE(27)
#define _ROUTEEID_29 _ROUTEEID_28, ROUTE(28)
#define _ROUTEEID_30 _ROUTEEID_29, ROUTE(29)
#define _ROUTEEID_31 _ROUTEEID_30, ROUTE(30)
#define _ROUTEEID_32 _ROUTEEID_31, ROUTE(31)
#define _ROUTEEID_33 _ROUTEEID_32, ROUTE(32)
#define _ROUTEEID_34 _ROUTEEID_33, ROUTE(33)
#define _ROUTEEID_35 _ROUTEEID_34, ROUTE(34)
#define _ROUTEEID_36 _ROUTEEID_35, ROUTE(35)
#define _ROUTEEID_37 _ROUTEEID_36, ROUTE(36)
#define _ROUTEEID_38 _ROUTEEID_37, ROUTE(37)
#define _ROUTEEID_39 _ROUTEEID_38, ROUTE(38)
#define _ROUTEEID_40 _ROUTEEID_39, ROUTE(39)

#define _ROUTEEID(n) _ROUTEEID_##n
#define ROUTEEID(n) _ROUTEEID(n)

#define TO(i,t) PEID( inputs[i].to[t] )

#define TO1(i) CEID( inputs[i].consumer), TO(i,0)
#define TO2(i) TO1(i), TO(i,1)
#define TO3(i) TO2(i), TO(i,2)
#define TO4(i) TO3(i), TO(i,3)
#define TO5(i) TO4(i), TO(i,4)
#define TO6(i) TO5(i), TO(i,5)
#define TO7(i) TO6(i), TO(i,6)
#define TO8(i) TO7(i), TO(i,7)
#define TO9(i) TO8(i), TO(i,8)
#define TO10(i) TO9(i), TO(i,9)
#define TO11(i) TO10(i), TO(i,10)
#define TO12(i) TO11(i), TO(i,11)
#define TO13(i) TO12(i), TO(i,12)
#define TO14(i) TO13(i), TO(i,13)
#define TO15(i) TO14(i), TO(i,14)
#define TO16(i) TO15(i), TO(i,15)
#define TO17(i) TO16(i), TO(i,16)
#define TO18(i) TO17(i), TO(i,17)
#define TO19(i) TO18(i), TO(i,18)
#define TO20(i) TO19(i), TO(i,19)
#define TO21(i) TO20(i), TO(i,20)
#define TO22(i) TO21(i), TO(i,21)
#define TO23(i) TO22(i), TO(i,22)
#define TO24(i) TO23(i), TO(i,23)
#define TO25(i) TO24(i), TO(i,24)
#define TO26(i) TO25(i), TO(i,25)
#define TO27(i) TO26(i), TO(i,26)
#define TO28(i) TO27(i), TO(i,27)
#define TO29(i) TO28(i), TO(i,28)
#define TO30(i) TO29(i), TO(i,29)
#define TO31(i) TO30(i), TO(i,30)
#define TO32(i) TO31(i), TO(i,31)
#define TO33(i) TO32(i), TO(i,32)
#define TO34(i) TO33(i), TO(i,33)
#define TO35(i) TO34(i), TO(i,34)
#define TO36(i) TO35(i), TO(i,35)
#define TO37(i) TO36(i), TO(i,36)
#define TO38(i) TO37(i), TO(i,37)
#define TO39(i) TO38(i), TO(i,38)
#define TO40(i) TO39(i), TO(i,39)

#define TON(n,i) TO##n(i)
#define TOEID(n,i) TON(n,i) // Usage: TOEID(num_to_elements, action_index)
#define CONSEID() 

#define ACTION1(n) TOEID(n,0)
#define ACTION2(n) ACTION1(n), TOEID(n,1)
#define ACTION3(n) ACTION2(n), TOEID(n,2)
#define ACTION4(n) ACTION3(n), TOEID(n,3)
#define ACTION5(n) ACTION4(n), TOEID(n,4)
#define ACTION6(n) ACTION5(n), TOEID(n,5)
#define ACTION7(n) ACTION6(n), TOEID(n,6)
#define ACTION8(n) ACTION7(n), TOEID(n,7)
#define ACTION9(n) ACTION8(n), TOEID(n,8)
#define ACTION10(n) ACTION9(n), TOEID(n,9)
#define ACTION11(n) ACTION10(n), TOEID(n,10)
#define ACTION12(n) ACTION11(n), TOEID(n,11)
#define ACTION13(n) ACTION12(n), TOEID(n,12)
#define ACTION14(n) ACTION13(n), TOEID(n,13)
#define ACTION15(n) ACTION14(n), TOEID(n,14)
#define ACTION16(n) ACTION15(n), TOEID(n,15)
#define ACTION17(n) ACTION16(n), TOEID(n,16)
#define ACTION18(n) ACTION17(n), TOEID(n,17)
#define ACTION19(n) ACTION18(n), TOEID(n,18)
#define ACTION20(n) ACTION19(n), TOEID(n,19)
#define ACTION21(n) ACTION20(n), TOEID(n,20)
#define ACTION22(n) ACTION21(n), TOEID(n,21)
#define ACTION23(n) ACTION22(n), TOEID(n,22)
#define ACTION24(n) ACTION23(n), TOEID(n,23)
#define ACTION25(n) ACTION24(n), TOEID(n,24)
#define ACTION26(n) ACTION25(n), TOEID(n,25)
#define ACTION27(n) ACTION26(n), TOEID(n,26)
#define ACTION28(n) ACTION27(n), TOEID(n,27)
#define ACTION29(n) ACTION28(n), TOEID(n,28)
#define ACTION30(n) ACTION29(n), TOEID(n,29)
#define ACTION31(n) ACTION30(n), TOEID(n,30)
#define ACTION32(n) ACTION31(n), TOEID(n,31)
#define ACTION33(n) ACTION32(n), TOEID(n,32)
#define ACTION34(n) ACTION33(n), TOEID(n,33)
#define ACTION35(n) ACTION34(n), TOEID(n,34)
#define ACTION36(n) ACTION35(n), TOEID(n,35)
#define ACTION37(n) ACTION36(n), TOEID(n,36)
#define ACTION38(n) ACTION37(n), TOEID(n,37)
#define ACTION39(n) ACTION38(n), TOEID(n,38)
#define ACTION40(n) ACTION39(n), TOEID(n,39)


#define ACTIONN(n,t) ACTION##n(t)
#define ACTIONEID(n,t) ACTIONN(n,t) // Usage: ACTIONEID(num_actions, num_to_elements)

#define INDICATOR_EID(i) \
  CEID(indicators[i].eventOn), \
  CEID(indicators[i].eventOff), \
  CEID(indicators[i].eventFlash)

#define INDICATORS_12_EID \
  INDICATOR_EID(0),  INDICATOR_EID(1),  INDICATOR_EID(2),  \
  INDICATOR_EID(3),  INDICATOR_EID(4),  INDICATOR_EID(5),  \
  INDICATOR_EID(6),  INDICATOR_EID(7),  INDICATOR_EID(8),  \
  INDICATOR_EID(9),  INDICATOR_EID(10), INDICATOR_EID(11)


/*
 Leave uncomment to disable blue/gold other as it will slowdown opening in JMRI
*/

#define OLCB_NO_BLUE_GOLD  