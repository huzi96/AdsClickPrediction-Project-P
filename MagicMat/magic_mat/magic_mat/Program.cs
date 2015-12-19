using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace magic_mat
{
    class Program
    {
        static void Main(string[] args)
        {
            Magic magic = new Magic(1);
            Console.WriteLine("Magic built succeed");
            for (int i = 0; i < 100; i++)
            {
                Console.WriteLine("iter {0}", i);
                if (i % 2 == 1)
                {
                    magic.mat.iter_id();
                }
                else
                    magic.mat.iter_pos();
            }

            magic.sort_for_output();
            magic.dump();
        }

    }

    public class Magic
    {
        static string data_file = @"magic_mat.bin";
        public Mat mat;

        public void sort_for_output()
        {
            Array.Sort(mat.poss);
            mat.iter_pos(0);
            Array.Sort(mat.ids);
        }

        public void dump()
        {
            string time_stamp = DateTime.Now.Minute.ToString() + DateTime.Now.Second.ToString();
            FileStream posout = new FileStream("pos_out"+time_stamp+".txt", FileMode.Create);
            StreamWriter pos_w = new StreamWriter(posout);
            foreach (Item a_item in mat.poss)
            {
                pos_w.WriteLine("{0}\t{1}", a_item.num, a_item.score);
            }
            pos_w.Close();
            posout.Close();
            
            FileStream idout = new FileStream("id_out"+time_stamp+".txt", FileMode.Create);
            StreamWriter id_w = new StreamWriter(idout);
            foreach (Item a_item in mat.ids)
            {
                id_w.WriteLine("{0}\t{1}", a_item.num, a_item.score);
            }
            id_w.Close();
            idout.Close();

        }
        static public void save_file(Mat m)
        {
            Serialize(m);
        }
        public void save_file()
        {
            Serialize(mat);
        }
        static public void Serialize(Mat data)
        {
            FileStream fs = new FileStream(data_file, FileMode.OpenOrCreate);
            BinaryFormatter formattor = new BinaryFormatter();
            formattor.Serialize(fs, data);
            fs.Close();
        }
        static public void Deserialize( Mat res)
        {
            FileStream fs = new FileStream(data_file, FileMode.OpenOrCreate);
            BinaryFormatter formatter = new BinaryFormatter();
            res = (Mat)formatter.Deserialize(fs);
            fs.Close();
        }
        public Magic(int flag)
        {
            if (flag == 1)
            {
                mat = new Mat();
                mat.init();
            }
            else {
                Deserialize(mat);
            }
        }
        [Serializable]
        public class Item:IComparable
        {
            public int num { set; get; }

            public double score;
            public List<int> relations;
            public int list_len
            {
                get
                {
                    return relations.Count;
                }
            }
            public Item()
            {
                relations = new List<int>();
                score = 1;
            }
            override public string ToString()
            {
                return score.ToString();
            }

            public int CompareTo(object obj)
            {
                return -score.CompareTo(((Item)obj).score);
            }
        }

        [Serializable]
        public class Mat
        {
            const int POSS = 80851;
            const int IDS = 646843;
            public Item[] ids, poss;

            public Mat()
            {
                ids = new Item[IDS + 2];
                poss = new Item[POSS + 2];
                for (int i = 0; i < IDS + 2; i++)
                {
                    ids[i] = new Item();
                }
                for (int j = 0; j < POSS + 2; j++)
                {
                    poss[j] = new Item();
                }
            }
            public void init()
            {
                FileStream pairs = new FileStream("pairs.txt", FileMode.Open);
                StreamReader rd = new StreamReader(pairs);
                string str;
                while ((str = rd.ReadLine()) != null)
                {
                    string[] spl = str.Split();
                    int id_num = int.Parse(spl[0]);
                    int pos_num = int.Parse(spl[1]);
                    ids[id_num].num = id_num;
                    poss[pos_num].num = pos_num;
                    ids[id_num].relations.Add(pos_num);
                    poss[pos_num].relations.Add(id_num);
                }
                Console.WriteLine("read ok");
            }
            public void iter_id()
            {
                for (int i = 0; i < IDS; i++)
                {
                    double avg_score = ids[i].score / ids[i].list_len;
                    foreach (int pos_p in ids[i].relations)
                    {
                        poss[pos_p].score += avg_score;
                    }
                    ids[i].score = 0;
                }
            }
            public void iter_pos(int flag = 1)
            {
                for (int i = 0; i < POSS; i++)
                {
                    double avg_score = poss[i].score / poss[i].list_len;
                    foreach (int id_p in poss[i].relations)
                    {
                        ids[id_p].score += avg_score;
                    }
                    if(flag == 1)poss[i].score = 0;
                }
            }
        }
    }


}
