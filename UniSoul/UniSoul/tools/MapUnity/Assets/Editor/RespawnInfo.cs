using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using System.Text;


public class RespwanInfo : EditorWindow
{

    //[MenuItem("Window/リスポーン 出力")]
    public static void ShowWindow()
    {
        GameObject respawn = GameObject.Find("Respawn");
        if (respawn == null)
        {
            Debug.Log("コリジョンの親が作られていません。");
        }
        Transform[] collisions = respawn.GetComponentsInChildren<Transform>();
        string headerTxt = "";
        foreach (Transform tr in collisions)
        {
            if (tr.gameObject == respawn)
            {
                //親は無視する。
                continue;
            }
            headerTxt += string.Format("//{0}\n", tr.name);
            headerTxt += "{\n";
            headerTxt += string.Format("\tD3DXVECTOR3({0:f}f, {1:f}f, {2:f}f),             //平行移動\n", tr.position.x, tr.position.y, tr.position.z);
            headerTxt += string.Format("\tD3DXQUATERNION({0:f}f, {1:f}f, {2:f}f, {3:f}f ),    //回転\n", tr.rotation.x, tr.rotation.y, tr.rotation.z, tr.rotation.w);
            headerTxt += string.Format("\tD3DXVECTOR3({0:f}f, {1:f}f, {2:f}f ),            //拡大\n", tr.lossyScale.x, tr.lossyScale.y, tr.lossyScale.z);
            headerTxt += "},\n";
        }

        StreamWriter sw = new StreamWriter("C:/GitHub/Game/UniSoul/UniSoul/RespawnInfo.h", false, Encoding.UTF8);
        sw.Write(headerTxt);
        sw.Close();
    }
}
