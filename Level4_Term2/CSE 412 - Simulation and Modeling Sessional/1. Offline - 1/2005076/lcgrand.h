#ifndef LCGRAND_H
#define LCGRAND_H

#ifdef __cplusplus
extern "C" {
#endif

float lcgrand(int stream);
void lcgrandst(long zset, int stream);
long lcgrandgt(int stream);

#ifdef __cplusplus
}
#endif

#endif
