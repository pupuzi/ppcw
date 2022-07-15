using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//绑定到camera上,目标是需要加装摄像机的角色
public class PPObjMoveCam : MonoBehaviour
{
    Vector3 posOfs;
    static Vector3 posLast;

    [SerializeField]
    private GameObject role;

    private void CameraRotate(GameObject oPlayer, Camera oCam)
    {
        var mouse_x = Input.GetAxis("Mouse X") * 3;
        var mouse_y = -Input.GetAxis("Mouse Y") * 3;

        oCam.transform.position = oCam.transform.position + posOfs;
        oCam.transform.RotateAround(oPlayer.transform.position, Vector3.up, mouse_x);
        //oCam.transform.RotateAround(oPlayer.transform.position, oPlayer.transform.right, mouse_y);
        //if (transform.localEulerAngles.z != 0)
        //{
        //    float rotX = transform.localEulerAngles.x;
        //    float rotY = transform.localEulerAngles.y;
        //    oCam.transform.localEulerAngles = new Vector3(rotX, rotY, 0);
        //}
    }

    void Start()
    {
        posLast = role.transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        if(role.GetComponent<PPObjMove>().IsEsc())
        {
            return;
        }

        posOfs = role.transform.position - posLast; 
        CameraRotate(role, gameObject.GetComponent<Camera>());
        posLast = role.transform.position;
    }
}
