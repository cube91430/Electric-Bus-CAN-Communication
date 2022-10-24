void slave() {
    CAN.init_Mask(0, 1, myMask);
    CAN.init_Filt(0, 1, 0x0CF00500);

    CAN.init_Mask(1, 1, myMask);
    CAN.init_Filt(1, 1, 0x0CF00400);

    CAN.init_Mask(1, 1, 0X0DFFFFFF);
    CAN.init_Filt(2, 1, 0x0D000020);

    CAN.init_Mask(1, 1, 0X0DFFFFFF);
    CAN.init_Filt(3, 1, 0x0D000021);

    CAN.init_Mask(1, 1, 0X0DFFFFFF);
    CAN.init_Filt(5, 1, 0x0D000022);

    CAN.init_Mask(1, 1, 0X0DFFFFFF);
    CAN.init_Filt(5, 1, 0x0D000023);
}

void master(){
    CAN.init_Mask(0, 1, myMask);
    CAN.init_Filt(0, 1, 0x0CF00500);

    CAN.init_Mask(1, 1, myMask);
    CAN.init_Filt(1, 1, 0x0CF00400);

    CAN.init_Mask(1, 1, 0X0DFFFFFF);
    CAN.init_Filt(2, 1, 0x0D000010);

    CAN.init_Mask(1, 1, 0X0DFFFFFF);
    CAN.init_Filt(3, 1, 0x0D000011);

    CAN.init_Mask(1, 1, 0X0DFFFFFF);
    CAN.init_Filt(5, 1, 0x0D000012);

    CAN.init_Mask(1, 1, 0X0DFFFFFF);
    CAN.init_Filt(5, 1, 0x0D000013);
}
