using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using System.Text;


public class EnemyPosInfo : EditorWindow
{
    //[MenuItem("Window/オブジェクトの配置情報 出力")]
    public static void ShowWindow()
    {
        //マップ上に配置されたオブジェクトの親を取得。
        GameObject Object = GameObject.Find("MapEnemy");
        //親が作られていない場合の処理
        if (Object == null)
        {
            Debug.Log("エネミーのオブジェクトの親が作られていません。");
        }

        Transform[] Objects = Object.GetComponentsInChildren<Transform>();
        string headerTxt = "";

        foreach (Transform tr in Objects)
        {
            if (tr.tag == "Enemy")
            {
                if (tr.gameObject == Object)
                {
                    continue;
                }
                headerTxt += string.Format("//{0}\n", tr.name);
                headerTxt += "{\n";
                headerTxt += string.Format("\t\"{0}\",\n", tr.name);
                headerTxt += string.Format("\tD3DXVECTOR3({0:f}f, {1:f}f, {2:f}f),             //平行移動\n", tr.position.x, tr.position.y, tr.position.z);
                headerTxt += string.Format("\tD3DXQUATERNION({0:f}f, {1:f}f, {2:f}f, {3:f}f ),    //回転\n", tr.rotation.x, tr.rotation.y, tr.rotation.z, tr.rotation.w);
                headerTxt += string.Format("\tD3DXVECTOR3({0:f}f, {1:f}f, {2:f}f ),            //拡大\n", tr.lossyScale.x, tr.lossyScale.y, tr.lossyScale.z);
                headerTxt += "},\n";
            }
        }

        StreamWriter sw = new StreamWriter("C:/Github/Game/UniSoul/UniSoul/EnemyPosInfo.h", false, Encoding.UTF8);
        sw.Write(headerTxt);
        sw.Close();
    }
}

