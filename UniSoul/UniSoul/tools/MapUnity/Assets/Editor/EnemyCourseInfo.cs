using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using System.Text;

public class EnemyCourse : MonoBehaviour
{

    //[MenuItem("Window/敵のコース定義の配置情報 出力")]
    public static void ShowWindow()
    {
        GameObject cource = GameObject.Find("Cource");
        if (cource == null)
        {
            Debug.Log("コース定義の親が作られていません。");
        }
        Transform[] courcePoint = cource.GetComponentsInChildren<Transform>();
        string headerTxt = "";
        foreach (Transform tr in courcePoint)
        {
            if (tr.gameObject == cource)
            {
                continue;
            }
            headerTxt += string.Format("D3DXVECTOR3({0:f}f, {1:f}f, {2:f}f), //{3}\n", tr.position.x, tr.position.y, tr.position.z, tr.name);
        }

        StreamWriter sw = new StreamWriter("C:/GitHub/Game/UniSoul/UniSoul/EnemyCource.h", false, Encoding.UTF8);
        sw.Write(headerTxt);
        sw.Close();
    }
}