#ifndef LYOKOCOIN_CHAINPARAMSSEEDS_H
#define LYOKOCOIN_CHAINPARAMSSEEDS_H
/**
 * List of fixed seed nodes for the lyokocoin network
 * @generated by contrib/seeds/generate-seeds.py
 *
 * Each line contains a 16-byte IPv6 address and a port.
 * IPv4 as well as onion addresses are wrapped inside a IPv6 address accordingly.
 */
static SeedSpec6 pnSeed6_main[] = {
    {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x0d,0x39,0xbd,0x65}, 5333}
};

static SeedSpec6 pnSeed6_test[] = {
    {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xc0,0xa8,0x01,0x30}, 5333},
    {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xc0,0xa8,0x01,0x26}, 5333},
};
#endif // LYOKOCOIN_CHAINPARAMSSEEDS_H
