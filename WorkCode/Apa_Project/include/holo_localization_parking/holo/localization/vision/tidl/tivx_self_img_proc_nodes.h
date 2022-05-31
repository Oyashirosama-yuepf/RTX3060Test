#ifndef TIVX_SELF_PROC_NODES_H_
#define TIVX_SELF_PROC_NODES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <VX/vx.h>

VX_API_ENTRY vx_node VX_API_CALL tivxSelfHirainThresholdNode(vx_graph graph, vx_tensor input1, vx_tensor input2,
                                                             vx_tensor scores, vx_tensor indexs);

#ifdef __cplusplus
}
#endif

#endif /* TIVX_IMG_PROC_NODES_H_ */
