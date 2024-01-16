// import { useRef, useState, useEffect } from "react";

// const useFetch = (fulladdress) => {
//   const cache = useRef({});
//   const [status, setStatus] = useState("idle");
//   const [data, setData] = useState([]);

//   useEffect(() => {
//     if (!fulladdress) return;
//     const fetchData = async () => {
//       setStatus("fetching");
//       if (cache.current[fulladdress]) {
//         const data = cache.current[fulladdress];
//         setData(data);
//         setStatus("fetched");
//       } else {
//         const params = {
//           address: fulladdress,
//         };
//         const response = await fetch(
//           `https://realty-mole-property-api.p.rapidapi.com/properties?address=${fulladdress}`,
//           {
//             method: "GET",
//             headers: {
//               "x-rapidapi-host": "realty-mole-property-api.p.rapidapi.com",
//               "x-rapidapi-key":
//                 "7bdd8d7c63msh369accce28b05f5p1bc7a3jsn70c5720ff919",
//             },
//           }
//         );
//         const data = await response.json();
//         cache.current[fulladdress] = data; // set response in cache;
//         setData(data);
//         setStatus("fetched");
//       }
//     };

//     fetchData();
//   }, [fulladdress]);
//   return { status, data };
// };

// export default useFetch;
