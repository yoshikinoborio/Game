using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using System.Text;


public class MapObjectInfo : EditorWindow
{
    //[MenuItem("Window/オブジェクトの配置情報 出力")]
    public static void ShowWindow()
    {
        //マップ上に配置されたオブジェクトの親を取得。
        GameObject Object = GameObject.Find("MapObject");
        //親が作られていない場合の処理
        if (Object == null)
        {
            Debug.Log("マップオブジェクトの親が作られていません。");
        }

        Transform[] Objects = Object.GetComponentsInChildren<Transform>();
        string headerTxt = "";

        //foreachはコレクション(配列、リスト、辞書)のすべての要素を1回ずつ読み出す構文。
        foreach (Transform tr in Objects)
        {
            if (tr.tag == "Map")
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
         StreamWriter sw = new StreamWriter("C:/GitHub/Game/UniSoul/UniSoul/locationInfo.h", false, Encoding.UTF8);
        sw.Write(headerTxt);
        sw.Close();
    }
}