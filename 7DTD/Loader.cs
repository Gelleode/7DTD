﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
namespace Cheat
{
    class Loader : MonoBehaviour
    {
		public static void Init()
		{


		//	Loader.hackObject.AddComponent<Globals>();
			Loader.hackObject.AddComponent<Cheat.Esp.Zombie>();
			UnityEngine.Object.DontDestroyOnLoad(hackObject);

		}
		public static GameObject hackObject = new GameObject(); // make bool in a public static class and check if its true constantly as extra auth shit
	}
}